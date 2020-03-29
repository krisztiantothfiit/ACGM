#include "..\include\ACGM_RayTracer_lib\PhongShader.h"
#include <iostream>
#include <glm\gtx\string_cast.hpp>

acgm::PhongShader::PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular)
	: color_(color), shininess_(shininess), ambient_(ambient), diffuse_(diffuse), specular_(specular)
{
}

const cogs::Color3f acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    float angle = glm::acos(glm::dot(input.normal, input.direction_to_light) / glm::dot(glm::length(input.normal), glm::length(input.direction_to_light)));
    glm::vec3 h = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float diffuseIntensity = 0;
    float specularIntensity = 0;

    if (!input.is_point_in_shadow) {
        diffuseIntensity = diffuse_ * (ambient_ + (1 - ambient_) * input.light_intensity) * glm::cos(angle);
        specularIntensity = specular_ * (ambient_ + (1 - ambient_) * input.light_intensity) * pow(glm::dot(h, input.normal), shininess_);
    }

    return (color_ * ambient_) + (color_ * diffuseIntensity) + (cogs::color::WHITE * specularIntensity);
}
