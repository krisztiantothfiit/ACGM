#pragma once
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib\PhongShader.h>
#include <COGS/Color.h>
#include <cmath>

namespace acgm
{
    //! Check-board Shader representation
    class CheckerShader : public Shader
    {
    public:
        //! CheckerShader constructor
        CheckerShader(float cube_size, const std::shared_ptr<acgm::Shader> shader0, const std::shared_ptr<acgm::Shader> shader1);
        //! CheckerShader destructor
        virtual ~CheckerShader() = default;
        //! Calculate shader color
        const ShaderOutput CalculateColor(const ShaderInput& input) override;

    private:
        //! Size of the cube
        float cube_size_;
        //! Shader of cube 1
        std::shared_ptr<acgm::Shader> shader0_;
        //! Shader of cube 2
        std::shared_ptr<acgm::Shader> shader1_;
    };
}
