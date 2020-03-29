#pragma once

#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/HitResult.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include "glm/glm.hpp";


namespace acgm
{
  //! Plane representation
  class Plane : public Model
  {
  public:
      //! Plane constructor
      Plane(const glm::vec3 &position, const glm::vec3 &normal);
      //! Plane destructor
      virtual ~Plane() = default;
      //! Get plane position
      const glm::vec3 &GetPosition() const;
      //! Get plane normal
      const glm::vec3 &GetNormal() const;
      //! Get plane color
      cogs::Color3f GetColor() const;
      //! Set plane color
      void SetColor(const cogs::Color3f& color);
      //! Calculate intersection with ray
      std::optional<HitResult> Intersect(const acgm::Ray& ray) const override;
     
  private:
      //! Position in the scene
      const glm::vec3 position_;
      //! Normal vector of the plane
      const glm::vec3 normal_;
      //! Color of the plane
      cogs::Color3f color_;      
  };
}
