#include <ACGM_RayTracer_lib/Light.h>
#include <glm/glm.hpp>

acgm::Light::Light()
{
}

glm::vec3 acgm::Light::GetDirectionToLight(const glm::vec3& point) const
{
	return glm::vec3();
}

float acgm::Light::GetIntensityAt(const glm::vec3& point) const
{
	return 0.0f;
}

float acgm::Light::GetDistanceTo(const glm::vec3& point) const
{
	return 0.0f;
}
