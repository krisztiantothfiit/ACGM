#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
    //! Phong Shader representation
    class PhongShader : public Shader
    {
    public:
        //! Phong shader constructor
        PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular);
        //! Phong shader destructor
        virtual ~PhongShader() = default;
        //! Calculate shader color
        const cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        //! Shader color
        cogs::Color3f color_;
        //! Shader material shininess
        float shininess_;
        //! Shader ambient constant
        float ambient_;
        //! Shader diffuse constant
        float diffuse_;
        //! Sahder specular constant
        float specular_;
    };
}
#pragma once