#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>

#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib/Model.h>
#include "Plane.h"



namespace acgm
{
  //! Scene representation
  class Scene
  {
  public:
    //! Scene constructor
    Scene(const std::shared_ptr<acgm::Camera> camera, const std::shared_ptr<acgm::Light> light, std::vector<std::shared_ptr<acgm::Model>> models);
    //! Scene destructor
    ~Scene() = default;
    //! RayTrace the scene
    void Raytrace(const hiro::draw::PRasterRenderer& renderer) const;
    //! Reset the scene
    void Reset(const hiro::draw::PRasterRenderer& renderer) const;

  private:
    //! Camera in the Scene
    std::shared_ptr<acgm::Camera> camera_;
    //! Light in the Scene
    std::shared_ptr<acgm::Light> light_;
    //! Models in the Scene
    std::vector<std::shared_ptr<acgm::Model>> models_;
  };
}
