#include "..\include\ACGM_RayTracer_lib\HitResult.h"

acgm::HitResult::HitResult()
{
	ray_param_ = 0.0f;
	normal_ = glm::vec3();
}


float acgm::HitResult::GetRayParam() const
{
	return ray_param_;
}

void acgm::HitResult::SetRayParam(float ray_param)
{
	ray_param_ = ray_param;
}

const glm::vec3& acgm::HitResult::GetNormal() const
{
	return normal_;
}

void acgm::HitResult::SetRayNormal(glm::vec3 normal)
{
	normal_ = normal;
}
