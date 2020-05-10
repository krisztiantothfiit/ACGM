#include "pch.h"

TEST(EnvironmentTests, BackgroundColorTest)
{
    const auto image = std::make_shared<acgm::Image>("enviro2.jpg");
    float uv_x = 0.352416098;
    float uv_y = 0.166666478;

    EXPECT_TRUE(image->GetColorAt(glm::vec2(uv_x, uv_y)) == cogs::Color3f(0.360784322, 0.462745100, 0.560784340));
}