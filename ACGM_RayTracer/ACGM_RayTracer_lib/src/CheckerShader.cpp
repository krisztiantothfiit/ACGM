#include "..\include\ACGM_RayTracer_lib\CheckerShader.h"

acgm::CheckerShader::CheckerShader(float cube_size, const std::shared_ptr<acgm::Shader> shader0, const std::shared_ptr<acgm::Shader> shader1)
    : cube_size_(cube_size), shader0_(shader0), shader1_(shader1)
{
}

const cogs::Color3f acgm::CheckerShader::CalculateColor(const ShaderInput& input) const
{
    float bias = 0.1;
    int cube = ((int)floor(input.point.x / cube_size_ + bias) + (int)floor(input.point.y / cube_size_ + bias) + (int)floor(input.point.z / cube_size_ + bias)) % 2;
    if (cube == 0) {
        return shader0_->CalculateColor(input);
    }
    
    return shader1_->CalculateColor(input);
}
