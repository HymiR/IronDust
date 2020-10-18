/*
 * Image.cpp
 *
 *  Created on: 31.03.2011
 *      Author: sam
 */


#include <irondust/gl/Image.hpp>
#include <irondust/gl/gl_error.hpp>
#include <irondust/util/log.hpp>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <glm/glm.hpp>

#include <stdexcept>


namespace irondust
{
    namespace gl
    {

        #define LOG_DEVIL_ERRORS()                                                   \
        {                                                                            \
            for(ILenum err = ilGetError(); err != IL_NO_ERROR; err = ilGetError()) { \
                LOG_ERROR << "DevIL_ERROR: " << iluErrorString(err) << std::endl;    \
            }                                                                        \
        }

        void Image::initDevIL()
        {
            static bool ilInitialized = false;

            if(ilInitialized)
                return;

            LOG_DEBUG << "initialize DevIL" << std::endl;
            ilInit();
            iluInit();
            ilutInit(); //need to initialize to ensure that the loading of images work as expected
            ilutRenderer(ILUT_OPENGL);

            ilInitialized = true;
            LOG_DEBUG << "initialized DevIL" << std::endl;
        }


        Image* Image::load(const std::string& fileName)
        {
            initDevIL();
            LOG_DEBUG << "load image: " << fileName << std::endl;

            ILuint img;
            ilGenImages(1, &img);
            ilBindImage(img);

            if(!ilLoadImage(fileName.c_str())) {
                LOG_ERROR << "can't load image: " << fileName << std::endl;
                LOG_DEVIL_ERRORS()
                ilDeleteImages(1, &img);
                throw std::runtime_error("can't load image: " + fileName);
            }

            // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
            // TODO check whether this flipping funcionality is what we want, especially for damn cube maps.
            ILinfo imageInfo;
            iluGetImageInfo(&imageInfo);
            if(imageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
                iluFlipImage();
            }

            return new Image(fileName, img);
        }

        std::shared_ptr<Image> Image::shared(const std::string& file)
        {
            return std::shared_ptr<Image>(load(file));
        }


        Image::Image(const std::string& fileName, ILuint img)
            : fileName(fileName)
            , img(img)
        {
        }


        Image::~Image()
        {
            ilDeleteImages(1, &img);
        }


        glm::uint Image::getWidth()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_WIDTH));
        }


        glm::uint Image::getHeight()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_HEIGHT));
        }


        glm::uint Image::getDepth()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_DEPTH));
        }


        glm::uvec3 Image::getDimensions()
        {
            return glm::uvec3(getWidth(), getHeight(), getDepth());
        }


        std::string Image::getName()
        {
            return fileName;
        }


        unsigned char* Image::getData()
        {
            ilBindImage(img);
            return ilGetData();
        }


        glm::uint Image::getBytesPerPixel()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_BPP));
        }


        glm::uint Image::getFormat()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_FORMAT));
        }


        glm::uint Image::getType()
        {
            ilBindImage(img);
            return glm::uint(ilGetInteger(IL_IMAGE_TYPE));
        }


        Image* loadImage(const std::string& fileName)
        {
            return Image::load(fileName);
        }
    }
}
