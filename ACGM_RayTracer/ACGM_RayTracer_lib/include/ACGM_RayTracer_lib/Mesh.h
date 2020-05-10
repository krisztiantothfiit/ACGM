#pragma once

#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include "glm/ext.hpp"
#include "glm/glm.hpp";


namespace acgm
{
    //! Mesh representation
    class Mesh : public Model
    {
    public:
        //! Mesh constructor
        Mesh(std::string file_name, glm::mat4 transform);
        //! Plane destructor
        virtual ~Mesh() = default;
        //! Calculate instersecion with Ray
        std::optional<HitResult> Intersect(const acgm::Ray& ray) override;

    private:
    };
}
#pragma once
