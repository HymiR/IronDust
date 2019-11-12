/*
 * Image.hpp
 *
 *  Created on: 31.03.2011
 *      Author: sam
 */


#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/fwd.hpp>

#include <string>


namespace irondust
{
    namespace gl
    {
        class Image
        {
        public:
            virtual ~Image();

            static Image* load(const std::string& fileName);

            glm::uint getWidth();
            glm::uint getHeight();
            glm::uint getDepth();

            glm::uint getFormat();
            glm::uint getType();
            glm::uint getBytesPerPixel();

            glm::uvec3 getDimensions();
            std::string getName();

            unsigned char* getData();

        protected:
            std::string fileName;
            unsigned int img;

            Image(const std::string& fileName, unsigned int img);

            static void initDevIL();
        };

        Image* loadImage(const std::string& fileName);
    }
}


#endif // IMAGE_HPP
