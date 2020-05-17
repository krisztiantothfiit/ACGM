#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/SunLight.h>
#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/PhongShader.h>
#include <ACGM_RayTracer_lib/CheckerShader.h>
#include <ACGM_RayTracer_lib/Image.h>
#include "glm/ext.hpp"
#include <iostream>
#include <COGS\Mesh.h>
#include <ACGM_RayTracer_lib\Mesh.h>
#include <HIRO\gui\GuiTypes.h>
#include <algorithm>

acgm::Scene::Scene(
    const std::shared_ptr<acgm::Camera> camera,
    const std::shared_ptr<acgm::Light> light,
    std::vector<std::shared_ptr<acgm::Model>> models,
    std::string enviro_image_file,
    glm::vec3 enviro_up,
    glm::vec3 enviro_seam,
    float bias,
    float index_of_refraction)
    : camera_(camera), light_(light), models_(models), enviro_image_file_(enviro_image_file), enviro_up_(enviro_up), enviro_seam_(enviro_seam), bias_(bias), index_of_refraction_(index_of_refraction)
{
    if (!enviro_image_file_.empty()) {
        image_ = std::make_shared<acgm::Image>(enviro_image_file_.c_str());
    }
}

void acgm::Scene::Raytrace(const hiro::draw::PRasterRenderer& renderer, const int maxReflectionDepth, const int maxRefractionDepth) const
{
  float y = tan(camera_->GetFovYRad() / 2);

  float dy = 2.0f * y / (float)renderer->GetResolution().y;
  float dx = 2.0f * camera_->GetAspectRatio() * y / (float)renderer->GetResolution().x;
  
#pragma omp parallel for
  for (int i = 0; i < renderer->GetResolution().x; i++) {
      float y2 = y;
      float x = camera_->GetAspectRatio() * (-1) * y2 + i * dx;
      for (int j = 0; j < renderer->GetResolution().y; j++) {
          // Camera ray creation
          Ray ray(camera_->GetPosition(), glm::normalize(camera_->GetForwardDirection() + x * camera_->GetRightDirection() + y2 * camera_->GetUpDirection()));
          ray.SetBias(bias_);

         //if(i > 350 && j > 175)
          renderer->SetPixel(i, j, Trace(ray, 0, maxReflectionDepth, 0, maxRefractionDepth));

          y2 -= dy;
      }
  }
}

void acgm::Scene::Reset(const hiro::draw::PRasterRenderer& renderer) const
{
    for (unsigned int i = 0; i < renderer->GetResolution().x; i++) {
        for (unsigned int j = 0; j < renderer->GetResolution().y; j++) {
            renderer->SetPixel(i, j, cogs::color::BLACK);
        }
    }
}

cogs::Color3f acgm::Scene::Trace(Ray ray, int currentReflectionDepth, const int maxReflectionDepth, int currentRefractionDepth, const int maxRefractionDepth) const
{
    // Ray model intersection
    float minT = INFINITY;
    int nearestModelIndex = -1;
    std::optional<HitResult> minHit;

    for (int k = 0; k < models_.size(); k++) {
        std::optional<HitResult> hit = models_[k]->Intersect(ray);
        if (hit && hit->GetRayParam() < minT) {
            minT = hit->GetRayParam();
            nearestModelIndex = k;
            minHit = hit;
        }
    }

    // If intersection was found
    if (minT != INFINITY && minT > camera_->GetZNear() && minT < camera_->GetZFar()) {
        // Intersection point calculation
        glm::vec3 intersectionPoint = ray.GetPoint(minT);
        glm::vec3 shadowPoint = intersectionPoint + minHit->GetNormal() * ray.GetBias();
        
        // Shadow ray creation
        Ray shadowRay(shadowPoint, light_->GetDirectionToLight(shadowPoint));
        shadowRay.SetBias(bias_);

        float minTToLight = INFINITY;

        // Check if point is in shadow
        for (int l = 0; l < models_.size(); l++) {
            std::optional<HitResult> hit = models_[l]->Intersect(shadowRay);
            if (hit && hit->GetRayParam() < minTToLight) {
                minTToLight = hit->GetRayParam();               
            }
        }
    
        // Ignore intersection if distance from point to light is greater than distance from shadow point to intersection point
        float tNear = light_->GetDistanceTo(shadowPoint);

        ShaderInput shaderInput = {
            shadowPoint,
            minHit->GetNormal(),
            glm::normalize(camera_->GetPosition() - shadowPoint),
            light_->GetDirectionToLight(shadowPoint),
            light_->GetIntensityAt(intersectionPoint),
            shadowRay.GetBias(),
            minTToLight < tNear
        };

        ShaderOutput shaderOutput = models_[nearestModelIndex]->GetShader()->CalculateColor(shaderInput);

        cogs::Color3f refractionColor;
        cogs::Color3f reflectionColor;
        bool tir = false;
        bool inside = false;
        glm::vec3 normal = minHit->GetNormal();
        normal = glm::normalize(normal);
        glm::vec3 dir = ray.GetDirection();

        // Check if intersection point is inside or outside of object
        if (glm::dot(dir, normal) > 0) {
            normal = -normal;
            inside = true;
        }

        // Refractions
        if (shaderOutput.transparency > 0.05f && currentRefractionDepth < maxRefractionDepth) {
            std::optional<acgm::Ray> refractionRay = ray.CreateRefractionRay(inside, shaderOutput.refractive_index, index_of_refraction_, dir, normal, intersectionPoint);
            if (refractionRay) {
                tir = false;
                // Recursive refraction
                refractionColor = Trace(refractionRay.value(), currentReflectionDepth, maxReflectionDepth, ++currentRefractionDepth, maxRefractionDepth);
            }                      
            // Total internal reflection
            else {
                if (currentReflectionDepth < maxReflectionDepth) {
                    tir = true;                   
                    // Recursive reflection
                    reflectionColor = Trace(ray.CreateReflectionRay(dir, normal, intersectionPoint), ++currentReflectionDepth, maxReflectionDepth, currentRefractionDepth, maxRefractionDepth);
                }
            }
        }

        // Reflections 
        if (!tir && shaderOutput.glossiness > 0.05f && currentReflectionDepth < maxReflectionDepth) {
            // Recursive reflection
            reflectionColor = Trace(ray.CreateReflectionRay(dir, normal, intersectionPoint), ++currentReflectionDepth, maxReflectionDepth, currentRefractionDepth, maxRefractionDepth);
        }

        // Final color combination
        if (tir) {
            return shaderOutput.transparency * reflectionColor + (1.0f - shaderOutput.transparency) * shaderOutput.color;
        }
        return shaderOutput.glossiness * reflectionColor + shaderOutput.transparency * refractionColor + (1.0f - shaderOutput.glossiness - shaderOutput.transparency) * shaderOutput.color;

    }
    // If intersection was not found
    else {
        if (image_) {
            return image_->GetColorAt(image_->CalculateUVCoordinates(ray, enviro_up_, enviro_seam_));
        }
        else {
            return cogs::color::BLACK;
        }
    }
}
