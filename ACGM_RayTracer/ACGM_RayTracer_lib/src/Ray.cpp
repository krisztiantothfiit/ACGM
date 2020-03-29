#include <ACGM_RayTracer_lib/Ray.h>

acgm::Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction)
	: origin_(origin), direction_(direction)
{
	bias_ = 0.0f;
}

const glm::vec3 &acgm::Ray::GetOrigin() const
{
	return origin_;
}

const glm::vec3 &acgm::Ray::GetDirection() const
{
	return direction_;
}

const glm::vec3& acgm::Ray::GetPoint(float t) const
{
	return origin_ + direction_ * t;
}

const float acgm::Ray::GetBias() const
{
	return bias_;
}

void acgm::Ray::SetBias(const float bias)
{
	bias_ = bias;
}
