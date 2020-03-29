#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/SunLight.h>
#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/PhongShader.h>
#include <ACGM_RayTracer_lib/CheckerShader.h>
#include "glm/ext.hpp"
#include <iostream>
#include <COGS\Mesh.h>
#include <ACGM_RayTracer_lib\Mesh.h>
#include <HIRO\gui\GuiTypes.h>
#include <algorithm>

acgm::Scene::Scene(const std::shared_ptr<acgm::Camera> camera, const std::shared_ptr<acgm::Light> light, std::vector<std::shared_ptr<acgm::Model>> models)
    : camera_(camera), light_(light), models_(models)
{
}

void acgm::Scene::Raytrace(const hiro::draw::PRasterRenderer& renderer) const
{
  float y = tan(camera_->GetFovYRad() / 2);
  float x = camera_->GetAspectRatio() * -1 * y;

  float dy = 2.0f * y / (float)renderer->GetResolution().y;
  float dx = 2.0f * camera_->GetAspectRatio() * y / (float)renderer->GetResolution().x;
  
  //std::optional<HitResult> hit;

#pragma omp parallel for
  for (int i = 0; i < renderer->GetResolution().x; i++) {
      float y2 = y;
      x = camera_->GetAspectRatio() * (-1) * y2 + i * dx;
      for (int j = 0; j < renderer->GetResolution().y; j++) {
          // Camera ray creation
          Ray ray(camera_->GetPosition(), glm::normalize(camera_->GetForwardDirection() + x * camera_->GetRightDirection() + y2 * camera_->GetUpDirection()));
          ray.SetBias(0.0001f);

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

          // Shadow calculation
          if (minT != INFINITY && minT > camera_->GetZNear() && minT < camera_->GetZFar()) {
              // Shadow ray creation
              glm::vec3 intersectionPoint = ray.GetPoint(minT);
              glm::vec3 shadowPoint = intersectionPoint + minHit->GetNormal() * ray.GetBias();
              Ray shadowRay(shadowPoint, light_->GetDirectionToLight(shadowPoint));
              shadowRay.SetBias(ray.GetBias());

              float minTToLight = INFINITY;

              // Check if point is in shadow
              for (int l = 0; l < models_.size(); l++) {
                  std::optional<HitResult> hit = models_[l]->Intersect(shadowRay);
                  // Ignore intersection if distance from point to light is greater than distance from shadow point to intersection point
                  float tNear = light_->GetDistanceTo(shadowPoint);
                  if (hit && hit->GetRayParam() < tNear) {
                      if (hit->GetRayParam() < minTToLight) {
                          minTToLight = hit->GetRayParam();
                      }
                  }
              }

              // If point is in shadow
              if (minTToLight != INFINITY && minT > minTToLight) {
                  ShaderInput shaderInput = {
                      shadowPoint,
                      minHit->GetNormal(),
                      glm::normalize(camera_->GetPosition() - shadowPoint),
                      light_->GetDirectionToLight(shadowPoint),
                      light_->GetIntensityAt(shadowPoint),
                      true
                  };
                  renderer->SetPixel(i, j, models_[nearestModelIndex]->GetShader()->CalculateColor(shaderInput));
              }
              // If point is not in shadow
              else {
                  ShaderInput shaderInput = {
                      shadowPoint,
                      minHit->GetNormal(),
                      glm::normalize(camera_->GetPosition() - shadowPoint),
                      light_->GetDirectionToLight(shadowPoint),
                      light_->GetIntensityAt(shadowPoint),
                      false
                  };
                  renderer->SetPixel(i, j, models_[nearestModelIndex]->GetShader()->CalculateColor(shaderInput));
              }
          }        
          y2 -= dy;
      }
  }
}

void acgm::Scene::Reset(const hiro::draw::PRasterRenderer& renderer) const
{
    for (int i = 0; i < renderer->GetResolution().x; i++) {
        for (int j = 0; j < renderer->GetResolution().y; j++) {
            renderer->SetPixel(i, j, cogs::color::BLACK);
        }
    }
}
