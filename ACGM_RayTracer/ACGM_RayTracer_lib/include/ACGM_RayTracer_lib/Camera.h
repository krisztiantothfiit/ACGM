#pragma once
#include <glm/glm.hpp>

namespace acgm
{
  //! A Camera representation
  class Camera
  {
  public:
    //! Camera constructor
    Camera(const glm::vec3 &position, const glm::vec3 &up_direction, const glm::vec3 &forward_direction, float z_near, float z_far, float fov_y_rad);
    //! Camera destructor
    virtual ~Camera() = default;
    //! Get camera position
    const glm::vec3 &GetPosition() const;
    //! Get camera target
    const glm::vec3 &GetTarget() const;
    //! Get camera up direction
    const glm::vec3 &GetUpDirection() const;
    //! Get camera look direction
    const glm::vec3 &GetForwardDirection() const;
    //! Get camera right direction
    const glm::vec3 &GetRightDirection() const;
    //! Get scene clipping near doundary
    float GetZNear() const;
    //! Get scene clipping far boundary
    float GetZFar() const;
    //! Get camera field of view
    float GetFovYRad() const;
    //! Get camera aspect ratio
    float GetAspectRatio() const;
    //! Set camera aspect ratio
    void SetAspectRatio(float aspect_ratio);

  private:
    //! Position in the scene
    const glm::vec3 position_;
    //! Target - the point the camera looks at
    glm::vec3 target_;
    //! Camera up direction
    const glm::vec3 up_direction_;
    //! Camera forward direction aka. look direction
    const glm::vec3 forward_direction_;
    //! Camera right direction
    glm::vec3 right_direction_;
    //! Scene clipping near boundary
    float z_near_;
    //! Scene clipping far boundary
    float z_far_;
    //! Camera field of view
    float fov_y_rad_;
    //! Camera aspect ratio
    float aspect_ratio_;
  };
}
