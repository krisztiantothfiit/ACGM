#include "pch.h"
#include <glm/gtc/epsilon.hpp>

TEST(ShaderTests, PhongColorTest)
{
    ShaderInput shader_input{
        glm::vec3(0.0f, 0.500000358f, 0.500100017f),
        glm::vec3(0.0f, 0.000000715255737f, 1.0f),
        glm::vec3(0.0f, -0.000000238434467f, 0.999999940f),
        glm::vec3(-0.421076f, 0.842151999f, 0.336861014f),
        1.0f,
        0.001f,
        false
    };

    const auto phong_shader = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.0196078f, 0.615686f, 1.0f), 90.0f, 0.2f, 0.8f, 0.8f, 0, 0, 0);
    
    EXPECT_TRUE(cogs::Color3f(0.00920566265f, 0.289057970f, 0.469489276f) == phong_shader->CalculateColor(shader_input).color);
}

TEST(ShaderTests, CheckerColorTest)
{
    ShaderInput shader_input{
        glm::vec3(1.11980879f, 1.70148206f, 0.0000999999975),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(-0.436498463f, 0.272280455f, 0.857515216f),
        glm::vec3(-0.267305523f, -0.128289983f, 0.955033660f),
        0.0f,
        0.001f,
        false
    };

    const auto phong_shader0 = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.701961f, 0.701961f, 0.701961f), 5.0f, 0.2f, 0.8f, 0.0f, 0, 0, 0);
    const auto phong_shader1 = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.901961f, 0.901961f, 0.901961f), 5.0f, 0.2f, 0.8f, 0.0f, 0, 0, 0);

    const auto checker_shader = std::make_shared<acgm::CheckerShader>(0.5f, phong_shader0, phong_shader1);
 
    EXPECT_TRUE(cogs::Color3f(0.318216741f, 0.318216741f, 0.318216741f) == checker_shader->CalculateColor(shader_input).color);
}
