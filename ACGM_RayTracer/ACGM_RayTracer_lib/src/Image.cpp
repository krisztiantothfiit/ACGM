#include <ACGM_RayTracer_lib/Image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <ACGM_RayTracer_lib/stb_image/stb_image.h>
#include <iostream>
#include <COGS/Color.h>

acgm::Image::Image(const char* enviro_image_file)
{
    channel_count_ = 3;
    img_data_ = stbi_load(enviro_image_file, &width_, &height_, &channels_, channel_count_);
}

acgm::Image::~Image() {
    stbi_image_free(img_data_);
}

cogs::Color3f acgm::Image::GetColorAt(const glm::vec2& uvs) const
{
    int x = round(uvs.y * width_);
    int y = round(uvs.x * height_);
    float r = img_data_[channel_count_ * (y * width_ + x)];
    float g = img_data_[channel_count_ * (y * width_ + x) + 1];
    float b = img_data_[channel_count_ * (y * width_ + x) + 2];

    return cogs::Color3f(r/255, g/255, b/255);
}

glm::vec2 acgm::Image::CalculateUVCoordinates(acgm::Ray& ray, const glm::vec3& enviro_up, const glm::vec3& enviro_seam) const
{
    float dot_product = glm::dot(ray.GetDirection(), enviro_up);
    float latitude = std::acos(dot_product);
    float longitude = glm::orientedAngle(glm::normalize(ray.GetDirection() - dot_product * enviro_up), enviro_seam, enviro_up);

    float uv_x = (latitude - 0) / (glm::pi<float>() - 0);
    float uv_y = (longitude + glm::pi<float>()) / (glm::pi<float>() + glm::pi<float>());
	
    return glm::vec2(uv_x, uv_y);
}
