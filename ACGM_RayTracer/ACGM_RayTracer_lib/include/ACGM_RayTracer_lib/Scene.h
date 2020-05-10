#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Image.h>
#include "Plane.h"


namespace acgm
{
  //! Scene representation
  class Scene
  {
  public:
    //! Scene constructor
    Scene(
        const std::shared_ptr<acgm::Camera> camera, 
        const std::shared_ptr<acgm::Light> light, 
        std::vector<std::shared_ptr<acgm::Model>> models, 
        std::string enviro_image_file,
        glm::vec3 enviro_up,
        glm::vec3 enviro_seam,
        float bias,
        float index_of_refraction);
    //! Scene destructor
    ~Scene() = default;
    //! RayTrace the scene
    void Raytrace(const hiro::draw::PRasterRenderer& renderer, const int maxReflectionDepth, const int maxRefractionDepth) const;
    //! Reset the scene
    void Reset(const hiro::draw::PRasterRenderer& renderer) const;
    //! Trace a ray
    cogs::Color3f Trace(acgm::Ray ray, int currentReflectionDepth, const int maxReflectionDepth, int currentRefractionDepth, const int maxRefractionDepth) const;
    
  private:
    //! Camera in the Scene
    std::shared_ptr<acgm::Camera> camera_;
    //! Light in the Scene
    std::shared_ptr<acgm::Light> light_;
    //! Models in the Scene
    std::vector<std::shared_ptr<acgm::Model>> models_;
    //! Environment file name
    std::string enviro_image_file_;
    //! Environment up vector
    glm::vec3 enviro_up_;
    //! Environment seam vector
    glm::vec3 enviro_seam_;
    //! Ray bias
    float bias_;
    //! Environment image
    std::shared_ptr<acgm::Image> image_;
    //! Scene index of refraction
    float index_of_refraction_;
  };
}
