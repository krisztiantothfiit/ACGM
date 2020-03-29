#include <ACGM_RayTracer_lib/PointLight.h>

acgm::PointLight::PointLight(float intensity, glm::vec3 position, float range, float linear_attenuation, float quadratic_attenuation)
	: intensity_(intensity), position_(position), range_(range), linear_attenuation_(linear_attenuation), quadratic_attenuation_(quadratic_attenuation)
{
}

glm::vec3 acgm::PointLight::GetDirectionToLight(const glm::vec3& point) const
{
	return glm::normalize(position_ - point);
}

float acgm::PointLight::GetIntensityAt(const glm::vec3& point) const
{
	float d = hypot(hypot(position_.x - point.x, position_.y - point.y), position_.z - point.z);
	float l = range_ / (range_ + d * linear_attenuation_);
	float q = pow(range_, 2) / (pow(range_, 2) + pow(d, 2) * quadratic_attenuation_);

	return l * q * intensity_;
}

float acgm::PointLight::GetDistanceTo(const glm::vec3& point) const
{
	return hypot(hypot(position_.x - point.x, position_.y - point.y), position_.z - point.z);
}
