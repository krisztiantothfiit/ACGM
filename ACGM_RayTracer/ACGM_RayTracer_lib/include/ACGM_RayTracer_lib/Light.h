#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Abstract base class for Scene light
    class Light
    {
    public:
        //! Light constructor - abstract
        explicit Light(); 
        //! Light destructor
        virtual ~Light() = default;
        //! Get direction vector to the light - abstract
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) = 0;
        //! Get intensity at a specific point - abstract
        virtual float GetIntensityAt(const glm::vec3& point) = 0;
        //! Get distance to a specific point - abstract
        virtual float GetDistanceTo(const glm::vec3& point) = 0;

    private:
    };
}
