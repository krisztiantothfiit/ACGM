#include <ACGM_RayTracer_lib/SunLight.h>

acgm::SunLight::SunLight(float intensity, glm::vec3 direction)
	: intensity_(intensity), direction_(direction)
{
}

float acgm::SunLight::GetIntensityAt(const glm::vec3& point)
{
	return intensity_;
}

glm::vec3 acgm::SunLight::GetDirectionToLight(const glm::vec3& point)
{
	return -direction_;
}

float acgm::SunLight::GetDistanceTo(const glm::vec3& point)
{
	return INFINITY;
}

