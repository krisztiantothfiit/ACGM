#include "..\include\ACGM_RayTracer_lib\PhongShader.h"
#include <iostream>
#include <glm\gtx\string_cast.hpp>

acgm::PhongShader::PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness, const float transparency, const float refractive_index)
	: color_(color), shininess_(shininess), ambient_(ambient), diffuse_(diffuse), specular_(specular), glossiness_(glossiness), transparency_(transparency), refractive_index_(refractive_index)
{
}

const ShaderOutput acgm::PhongShader::CalculateColor(const ShaderInput& input)
{
    float angle = glm::acos(glm::dot(input.normal, input.direction_to_light) / glm::dot(glm::length(input.normal), glm::length(input.direction_to_light)));
    glm::vec3 h = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float diffuseIntensity = 0;
    float specularIntensity = 0;
    

    if (!input.is_point_in_shadow) {
        angle = glm::cos(angle);
        // Tuto zakomentovanu cast poprosim nevsimat pri hodnoteni druhej casti projektu, je to experiment na toon shading bonus
        // co odprezentujem v uvedenom termine na stranke pre bonusy.
        /*bool toon = true;
        if (toon) {
            if (angle <= 0.25) {
                angle = 0;
            }
            else if (angle <= 0.5) {
                angle = 0.25;
            }
            else if (angle <= 0.75) {
                angle = 0.5;
            }
            else if (angle <= 1) {
                angle = 0.75;
            }
        }*/
        diffuseIntensity = diffuse_ * (ambient_ + (1 - ambient_) * input.light_intensity) * angle;
        specularIntensity = specular_ * (ambient_ + (1 - ambient_) * input.light_intensity) * pow(glm::dot(h, input.normal), shininess_);
    }

    ShaderOutput shaderOutput
    {
        (color_ * ambient_) + (color_ * diffuseIntensity) + (cogs::color::WHITE * specularIntensity),
        glossiness_,
        transparency_,
        refractive_index_
    };

    return shaderOutput;
}

