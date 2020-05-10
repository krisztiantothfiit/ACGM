#include "pch.h"

TEST(ReflectionTests, ReflectionRayCreationTest)
{
    acgm::Ray ray(glm::vec3(0, 0.5, 2), glm::vec3(-0.447214365, -0.447214365, -0.774595857));
    ray.SetBias(0.0001);
    glm::vec3 intersectionPoint(-0.5f, 0.0f, 1.13397694f);
    glm::vec3 normal(0.0f, 1.0f, 0.0f);

    const auto reflectionRay = ray.CreateReflectionRay(ray.GetDirection(), normal, intersectionPoint);
    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(-0.500044703, 0.0000447211437, 1.13389945), reflectionRay.GetOrigin()));
    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(-0.447214365, 0.447214365, -0.774595857), reflectionRay.GetDirection()));
}