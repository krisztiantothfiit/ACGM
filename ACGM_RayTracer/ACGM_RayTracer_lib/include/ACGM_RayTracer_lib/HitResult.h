#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! A Hit result representation
    class HitResult
    {
    public:
        //! HitResult constructor
        HitResult();
        //! Hitresult destructor
        virtual ~HitResult() = default;
        //! Get HitResult ray param
        float GetRayParam() const;
        //! Set HitResult ray param
        void SetRayParam(float ray_param);
        //! Get Hitresult normal
        const glm::vec3 &GetNormal() const;
        //! Set HitResult normal
        void SetRayNormal(glm::vec3 normal);

    private:
        //! Parameter of the hit
        float ray_param_;
        // Normal vector of the hit
        glm::vec3 normal_;
    };
}
