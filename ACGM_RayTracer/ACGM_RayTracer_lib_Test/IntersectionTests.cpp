#include "pch.h"

TEST(IntersectionTests, RayPlaneIntersectionTest)
{
    // Valid intersect from input file
    auto plane = std::make_shared<acgm::Plane>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    acgm::Ray ray(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(-0.447214365f, -0.447214365f, -0.774595857f));
    ray.SetBias(0.0001f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        1.11803210f,
        plane->Intersect(ray)->GetRayParam(),
        glm::epsilon<float>()));

    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(0.0f, 1.0f, 0.0f), plane->Intersect(ray)->GetNormal()));

    // Valid intersect ray perpendicular with plane
    plane = std::make_shared<acgm::Plane>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    acgm::Ray ray2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    ray.SetBias(0.0001f);

    EXPECT_TRUE(plane->Intersect(ray2)->GetRayParam() >= 0.0f);
    
    // Invalid intersect ray parallel with plane
    plane = std::make_shared<acgm::Plane>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    acgm::Ray ray3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    ray.SetBias(0.0001f);

    EXPECT_TRUE(plane->Intersect(ray3) == std::nullopt);
}

TEST(IntersectionTests, RayMeshIntersectionTest)
{
    const auto mesh = std::make_shared<acgm::Mesh>("bunny.fbx", glm::mat4(0.566312f, 0.41145f, 0, 0, -0.41145f, 0.566312f, 0, 0, 0, 0, 0.7f, 0, 0, 0, 0.5f, 1));
    acgm::Ray ray(glm::vec3(0.0f, 2.40000010f, 2.20000005f), glm::vec3(0.0f, -0.727013111f, -0.686623752f));
    ray.SetBias(0.0001f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        2.89628863f,
        mesh->Intersect(ray)->GetRayParam(),
        glm::epsilon<float>()));

    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(-0.119482398f, 0.992819428f, 0.00578153692f), mesh->Intersect(ray)->GetNormal()));
}

TEST(IntersectionTests, RaySphereIntersectionTest)
{
    const auto sphere = std::make_shared<acgm::Sphere>(glm::vec3(0.0f, 0.5f, 0.0f), 0.5f);
    acgm::Ray ray(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.000000228639692f, -1.0f));
    ray.SetBias(0.0001f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        1.5f,
        sphere->Intersect(ray)->GetRayParam(),
        glm::epsilon<float>()));

    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(0.0f, 0.000000715255737f, 1.0f), sphere->Intersect(ray)->GetNormal()));
}