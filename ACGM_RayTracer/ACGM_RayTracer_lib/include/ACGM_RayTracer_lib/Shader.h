#pragma once

#include <COGS/Color.h>
#include <glm/glm.hpp>

struct ShaderInput
{
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 direction_to_eye;
    glm::vec3 direction_to_light;
    float light_intensity;
    bool is_point_in_shadow;
};

namespace acgm
{
    //! Shader  - abstract base class for shader
    class Shader
    {
    public:
        //! Shader constructor
        explicit Shader();
        //! Shader destructor
        virtual ~Shader() = default;
        //! Calculate shader color - abstract
        virtual const cogs::Color3f CalculateColor(const ShaderInput &input) const;

    private: 
    };
}
