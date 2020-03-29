#include "..\include\ACGM_RayTracer_lib\Shader.h"

acgm::Shader::Shader()
{
}

const cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return cogs::color::BLACK;
}
