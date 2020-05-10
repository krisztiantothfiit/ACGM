#pragma once
#include <glm/glm.hpp>
#include <COGS\Color.h>

namespace acgm
{
    //! An Image representation
    class Image
    {
    public:
        //! Image constructor
        Image(const char* enviro_image_file);
        //! Image destructor
        ~Image();
        //! Get image color at specific uvs
        cogs::Color3f GetColorAt(const glm::vec2& uvs) const;
    private:
        //! Image data
        uint8_t* img_data_;
        //! Image width
        int width_;
        //! Image height
        int height_;
        //! Image color channels
        int channels_;
        //! Requested channel count
        int channel_count_;
    };
}
