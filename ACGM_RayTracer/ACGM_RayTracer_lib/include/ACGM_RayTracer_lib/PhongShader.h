#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
    //! Phong Shader representation
    class PhongShader : public Shader
    {
    public:
        //! Phong shader constructor
        PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness, const float transparency, const float refractive_index);
        //! Phong shader destructor
        virtual ~PhongShader() = default;
        //! Calculate shader color
        const ShaderOutput CalculateColor(const ShaderInput& input) override;

    private:
        //! Shader color
        cogs::Color3f color_;
        //! Shader material shininess
        float shininess_;
        //! Shader ambient constant
        float ambient_;
        //! Shader diffuse constant
        float diffuse_;
        //! Shader specular constant
        float specular_;
        //! Shader glossiness constant
        float glossiness_;
        //! Shader transparency constant
        float transparency_;
        //! Shader index of refraction
        float refractive_index_;
    };
}
#pragma once