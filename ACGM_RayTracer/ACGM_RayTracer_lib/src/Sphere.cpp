#include <glm/geometric.hpp>
#include <glm/gtc/epsilon.hpp>
#include <ACGM_RayTracer_lib/Sphere.h>



acgm::Sphere::Sphere(const glm::vec3 &position, float radius)
  : position_(position), radius_(radius)
{
}

std::optional<acgm::HitResult> acgm::Sphere::Intersect(const acgm::Ray &ray) const
{
  glm::vec3 oo = ray.GetOrigin() - position_;

  float A = glm::dot(ray.GetDirection(), ray.GetDirection());
  float B = -2.0f * glm::dot(oo, ray.GetDirection());
  float C = glm::dot(oo, oo) - radius_ * radius_;
  float D = B * B - 4.0f * A * C;

  if (D < 0)
  {
    return std::nullopt;
  }

  float sD = glm::sqrt(D);

  float t1 = 0.5f * (B + sD) / A;
  if (t1 < ray.GetBias())
  {
    t1 = INFINITY;
  }

  float t2 = 0.5f * (B - sD) / A;
  if (t2 < ray.GetBias())
  {
    t2 = INFINITY;
  }

  const float t = glm::min(t1, t2);
  if (glm::isinf(t) || t < 0.0f)
  {
    return std::nullopt;
  }

  HitResult hit;
  hit.SetRayParam(t);
  glm::vec3 intersectionPoint = ray.GetPoint(t);
  hit.SetRayNormal(glm::normalize(intersectionPoint - position_));
  return hit;
}

const glm::vec3 &acgm::Sphere::GetPosition() const
{
  return position_;
}

float acgm::Sphere::GetRadius() const
{
  return radius_;
}

