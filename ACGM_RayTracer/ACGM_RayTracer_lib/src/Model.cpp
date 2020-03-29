#include <ACGM_RayTracer_lib/Model.h>

acgm::Model::Model()
{
}

std::optional<acgm::HitResult> acgm::Model::Intersect(const acgm::Ray& ray) const
{
    return std::nullopt;
}

std::shared_ptr<acgm::Shader> acgm::Model::GetShader() const
{
    return shader_;
}

void acgm::Model::SetShader(const std::shared_ptr<acgm::Shader> shader)
{
    shader_ = shader;
}
