#include <ACGM_RayTracer_lib/Ray.h>

acgm::Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction)
	: origin_(origin), direction_(direction)
{
	bias_ = 0.0f;
}

const glm::vec3 &acgm::Ray::GetOrigin() const
{
	return origin_;
}

const glm::vec3 &acgm::Ray::GetDirection() const
{
	return direction_;
}

const glm::vec3 acgm::Ray::GetPoint(float t) const
{
	return origin_ + direction_ * t;
}

const float acgm::Ray::GetBias() const
{
	return bias_;
}

void acgm::Ray::SetBias(const float bias)
{
	bias_ = bias;
}

acgm::Ray acgm::Ray::CreateReflectionRay(glm::vec3 dir, glm::vec3 normal, glm::vec3 intersectionPoint) const
{
    // Construction of reflection ray
    glm::vec3 reflectionRayDirection = dir - 2 * glm::dot(dir, normal) * normal;
    reflectionRayDirection = glm::normalize(reflectionRayDirection);
    glm::vec3 reflectionPoint = intersectionPoint + reflectionRayDirection * bias_;
    Ray reflectionRay(reflectionPoint, reflectionRayDirection);
    reflectionRay.SetBias(bias_);

    return reflectionRay;
}

std::optional<acgm::Ray> acgm::Ray::CreateRefractionRay(bool inside, float refractive_index, float index_of_refraction, glm::vec3 dir, glm::vec3 normal, glm::vec3 intersectionPoint) const
{
    float n, n1, n2;

    float cosTheta1 = glm::dot(dir, normal);

    if (inside) {
        n1 = refractive_index;
        n2 = index_of_refraction;
    }
    else {
        n1 = index_of_refraction;
        n2 = refractive_index;
    }
    n = n1 / n2;

    float cosTheta2 = 1 - pow(n, 2) + pow(n, 2) * pow(cosTheta1, 2);

    if (cosTheta2 > 0) {
        // Construction of refraction ray
        cosTheta2 = sqrt(cosTheta2);
        glm::vec3 refractionRayDirection = n * dir - normal * (n * cosTheta1 + cosTheta2);
        refractionRayDirection = glm::normalize(refractionRayDirection);
        glm::vec3 refractionPoint = intersectionPoint + refractionRayDirection * bias_;
        Ray refractionRay(refractionPoint, refractionRayDirection);
        refractionRay.SetBias(bias_);

        return refractionRay;
    }
    return std::nullopt;
}
