#pragma once
#include "glm/glm.hpp";

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
      const glm::vec3& GetPoint(float t) const;
      //! Get Ray bias
      const float GetBias() const;
      //! Set Ray bias
      void SetBias(const float bias);

  private:
      //! Origin of the ray
      const glm::vec3 origin_;
      //! Direction of the ray
      const glm::vec3 direction_;
      //! Bias of the ray
      float bias_;
  };
}
