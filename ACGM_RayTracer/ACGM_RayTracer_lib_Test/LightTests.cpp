#include "pch.h"

TEST(LightTests, SunLightIntenstyTest)
{
    const auto sun_light = std::make_shared<acgm::SunLight>(1.0f, glm::vec3(0.421076f, -0.842152f, -0.336861f));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        1.0f,
        sun_light->GetIntensityAt(glm::vec3(0.0f, 0.5f, 0.5f)),
        glm::epsilon<float>()));
}

TEST(LightTests, PointLightIntensityTest)
{
    const auto point_light = std::make_shared<acgm::PointLight>(1, glm::vec3(0.0f, 3.0f, -2.0f), 50.0f, 0.0f, 1.0f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.980531096f,
        point_light->GetIntensityAt(glm::vec3(0.0f, 2.19999480f, 4.99989986f)),
        glm::epsilon<float>()));
}

TEST(LightTests, SpotLightIntensityTest)
{
    const auto spot_light = std::make_shared<acgm::SpotLight>(1.0f, glm::vec3(0.7f, 1.5f, 1.5f), 50.0f, 0.0f, 1.0f, glm::vec3(-0.313363f, -0.671492f, -0.671492), 40.0f, 3.0f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.997689068f,
        spot_light->GetIntensityAt(glm::vec3(-0.0000119482393f, 0.294459671f, 0.211340055f)),
        glm::epsilon<float>()));
}