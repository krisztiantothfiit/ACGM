#pragma once

#include <ACGM_RayTracer_lib/Light.h>
#include "glm/glm.hpp";


namespace acgm
{
    //! PointLight representation
    class PointLight : public Light
    {
    public:
        //! PointLight constructor
        PointLight(float intensity, glm::vec3 position, float range, float linear_attenuation, float quadratic_attenuation);
        //! PointLight destructor
        virtual ~PointLight() = default;
        //! Get direction to PointLight at a specific point
        glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        //! Get PointLight intensity at a specific point
        float GetIntensityAt(const glm::vec3& point) const override;
        //! Get PointLight distance to a specific point
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
    };
}
#pragma once
