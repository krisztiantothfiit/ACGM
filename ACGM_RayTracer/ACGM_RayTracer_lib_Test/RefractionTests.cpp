#include "pch.h"

TEST(RefractionTests, RefractionRayCreationTest)
{
    bool inside = false;
    float model_IOR = 1.60000002f;
    float air_IOR = 1.00029004f;
    acgm::Ray ray(glm::vec3(1.07331765, 0.971403897, 1.09595478), glm::vec3(-0.682078540, -0.186416879, -0.707119226));
    ray.SetBias(0.0001);
    glm::vec3 intersectionPoint(-0.42995286f, 0.560549438f, -0.462504268f);
    glm::vec3 normal(0.770047367f, -0.439450681f, -0.462504387f);

    const auto refractionRay = ray.CreateRefractionRay(inside, model_IOR, air_IOR, ray.GetDirection(), normal, intersectionPoint);
    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(-0.430050254, 0.560569048, -0.462515593), refractionRay->GetOrigin()));
    EXPECT_TRUE(glm_ext::AreEqual(glm::vec3(-0.974057078, 0.195979685, -0.113158584), refractionRay->GetDirection()));
}

TEST(RefractionTests, TotalInternalReflectionTest)
{
    bool inside = true;
    float model_IOR = 1.60000002f;
    float air_IOR = 1.00029004f;
    acgm::Ray ray(glm::vec3(-0.338145852, 0.498371094, -0.0736951232), glm::vec3(-0.697272837, 0.259550273, 0.668164909));
    ray.SetBias(0.0001);
    glm::vec3 intersectionPoint(-1.42649424, 0.903493881, 0.969219744);
    glm::vec3 normal(0.226494223, 0.0965061337, -0.969219863);

    EXPECT_TRUE(ray.CreateRefractionRay(inside, model_IOR, air_IOR, ray.GetDirection(), normal, intersectionPoint) == std::nullopt);
}