#pragma once
#include "glm/glm.hpp";
#include <optional>

namespace acgm
{
  //! Representation of a ray
  class Ray
  {
  public:
      //! Ray constructor
      Ray(const glm::vec3& origin, const glm::vec3& direction);
      //! Ray destructor
      virtual ~Ray() = default;
      //! Get Ray position
      const glm::vec3& GetOrigin() const;
      //! Get Ray direcction
      const glm::vec3& GetDirection() const;
      //! Get intersection point
      const glm::vec3 GetPoint(float t) const;
      //! Get Ray bias
      const float GetBias() const;
      //! Set Ray bias
      void SetBias(const float bias);
      //! Create reflection ray
      acgm::Ray CreateReflectionRay(glm::vec3 dir, glm::vec3 normal, glm::vec3 intersectionPoint) const;
      //! Create refraction ray
      std::optional<acgm::Ray> CreateRefractionRay(bool inside, float refractive_index, float index_of_refraction, glm::vec3 dir, glm::vec3 normal, glm::vec3 intersectionPoint) const;


  private:
      //! Origin of the ray
      const glm::vec3 origin_;
      //! Direction of the ray
      const glm::vec3 direction_;
      //! Bias of the ray
      float bias_;
  };
}
