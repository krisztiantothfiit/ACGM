#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/PointLight.h>

acgm::SpotLight::SpotLight(float intensity, glm::vec3 position, float range, float linear_attenuation, float quadratic_attenuation, glm::vec3 cone_direction, float cutoff_angle, float exponent)
	: intensity_(intensity), position_(position), range_(range), linear_attenuation_(linear_attenuation), quadratic_attenuation_(quadratic_attenuation), cone_direction_(cone_direction), cutoff_angle_(cutoff_angle), exponent_(exponent)
{
}

glm::vec3 acgm::SpotLight::GetDirectionToLight(const glm::vec3& point) const
{
	return glm::normalize(position_ - point);
}

float acgm::SpotLight::GetIntensityAt(const glm::vec3& point) const
{
    acgm::PointLight point_light(intensity_, position_, range_, linear_attenuation_, quadratic_attenuation_);
    float intensity = point_light.GetIntensityAt(point);

    glm::vec3 directionFromLightToPoint = glm::normalize(point - position_);
    float angle = glm::acos(glm::dot(directionFromLightToPoint, cone_direction_) / glm::dot(glm::length(directionFromLightToPoint), glm::length(cone_direction_)));
    angle = glm::degrees(angle);

    if (angle > cutoff_angle_) {
        return 0;
    }

    float decay = 1 - pow((angle / cutoff_angle_), exponent_);

    return intensity * decay;
}

float acgm::SpotLight::GetDistanceTo(const glm::vec3& point) const
{
	return hypot(hypot(position_.x - point.x, position_.y - point.y), position_.z - point.z);
}
