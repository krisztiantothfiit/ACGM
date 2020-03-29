#pragma once
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/HitResult.h>
#include <optional>

namespace acgm
{
  class Sphere : public Model
  {
  public:
    //! Sphere constructor
    Sphere(const glm::vec3 &position, float radius);
    //! Sphere destructor
    virtual ~Sphere() = default;
    //! Calculate intersection with ray
    std::optional<HitResult> Intersect(const acgm::Ray& ray) const override;
    //! Get sphere position
    const glm::vec3 &GetPosition() const;
    //! Get sphere radius
    float GetRadius() const;
  
  private:
    //! Position in the scene
    glm::vec3 position_;
    // Radius of the spere
    float radius_;
  };
}
