#include <ACGM_RayTracer_lib/Camera.h>

acgm::Camera::Camera(const glm::vec3 &position, const glm::vec3 &up_direction, const glm::vec3 &forward_direction, float z_near, float z_far, float fov_y_rad)
    : position_(position), up_direction_(-up_direction), forward_direction_(forward_direction), z_near_(z_near), z_far_(z_far), fov_y_rad_(fov_y_rad)
{
    aspect_ratio_ = 0.0f;
    target_ = forward_direction_ + position_;
    right_direction_ = -glm::cross(forward_direction_, up_direction_);
}

const glm::vec3 &acgm::Camera::GetPosition() const
{
    return position_;
}

const glm::vec3 &acgm::Camera::GetTarget() const
{
    return target_;
}

const glm::vec3 &acgm::Camera::GetUpDirection() const
{
    return up_direction_;
}

const glm::vec3 &acgm::Camera::GetForwardDirection() const
{
    return forward_direction_;
}

const glm::vec3 &acgm::Camera::GetRightDirection() const
{
    return right_direction_;
}

float acgm::Camera::GetZNear() const
{
	return z_near_;
}

float acgm::Camera::GetZFar() const
{
    return z_far_;
}

float acgm::Camera::GetFovYRad() const
{
    return fov_y_rad_;
}

float acgm::Camera::GetAspectRatio() const
{
    return aspect_ratio_;
}

void acgm::Camera::SetAspectRatio(float aspect_ratio)
{
    aspect_ratio_ = aspect_ratio;
}