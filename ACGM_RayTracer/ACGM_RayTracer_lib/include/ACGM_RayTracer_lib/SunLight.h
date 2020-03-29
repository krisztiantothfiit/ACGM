#pragma once

#include <ACGM_RayTracer_lib/Light.h>
#include "glm/glm.hpp";


namespace acgm
{
    //! SunLight representation
    class SunLight : public Light
    {
    public:
        //! SunLight constructor
        SunLight(float intensity, glm::vec3 direction);
        //! SunLight destructor
        virtual ~SunLight() = default;
        //! Get SunLight intensity at a specific point
        float GetIntensityAt(const glm::vec3& point) const override;
        //! Get direction to SunLight at a specific point
        glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        //! Get SunLight distance to a specific point
        float GetDistanceTo(const glm::vec3& point) const override;

    private:
        //! SunLight intensity
        float intensity_;
        //! SunLight direction
        glm::vec3 direction_;
        
    };
}
#pragma once
