#include <ACGM_RayTracer_lib/Plane.h>

acgm::Plane::Plane(const glm::vec3 &position, const glm::vec3 &normal)
	: position_(position), normal_(-normal)
{
	color_ = cogs::color::WHITE;
}

const glm::vec3 &acgm::Plane::GetPosition() const
{
	return position_;
}

const glm::vec3 &acgm::Plane::GetNormal() const
{
	return normal_;
}

cogs::Color3f acgm::Plane::GetColor() const
{
	return color_;
}

void acgm::Plane::SetColor(const cogs::Color3f& color)
{
	color_ = color;
}

std::optional<acgm::HitResult> acgm::Plane::Intersect(const acgm::Ray& ray) const
{
	glm::vec3 diff = position_ - ray.GetOrigin();
	float prod1 = glm::dot(diff, normal_);
	float prod2 = glm::dot(ray.GetDirection(), normal_);

	if (prod2 == 0) {
		return std::nullopt;
	}

	float t = prod1 / prod2;

	if (glm::isinf(t) || t < 0.0f)
	{
		return std::nullopt;
	}

	HitResult hit;
	hit.SetRayParam(t);
	hit.SetRayNormal(-glm::normalize(normal_));
	return hit;
}
