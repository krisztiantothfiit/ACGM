#pragma once

#include <ACGM_RayTracer_lib/Light.h>
#include "glm/glm.hpp";


namespace acgm
{
    //! SpotLight representation
    class SpotLight : public Light
    {
    public:
        //! SpotLight constructor
        SpotLight(float intensity, glm::vec3 position, float range, float linear_attenuation, float quadratic_attenuation, glm::vec3 cone_direction, float cutoff_angle, float exponent_);
        //! SpotLight destructor
        virtual ~SpotLight() = default;
        //! Get direction to SpotLight at a specific point
        glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        //! Get SpotLight intensity at a specific point
        float GetIntensityAt(const glm::vec3& point) const override;
        //! Get SpotLight distance to a specific point
        float GetDistanceTo(const glm::vec3& point) const override;

    private:
        //! Intensity of the light
        float intensity_;
        //! Position of the light in the scene
        glm::vec3 position_;
        //! Range of the light
        float range_;
        //! Linear attenuation factor of the light
        float linear_attenuation_;
        //! Quadratic attenuation factor of the light
        float quadratic_attenuation_;
        //! Direction of the SpotLight
        glm::vec3 cone_direction_;
        //! Cutoff angle of the SpotLight
        float cutoff_angle_;
        //! Exponent of the SpotLight
        float exponent_;
    };
}
#pragma once
