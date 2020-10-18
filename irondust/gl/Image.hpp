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
#include <memory>


namespace irondust
{
    namespace gl
    {
        class Image
        {
        public:
            virtual ~Image();

            static Image* load(const std::string& fileName);
            static std::shared_ptr<Image> shared(const std::string& file);

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

        // TODO remove that...
        Image* loadImage(const std::string& fileName);
    }
}


#endif // IMAGE_HPP
