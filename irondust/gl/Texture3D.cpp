/*
 * Texture3D.cpp
 *
 *  Created on: 21.05.2011
 *      Author: sam
 */


#include <irondust/gl/Texture3D.hpp>
#include <irondust/gl/gl_error.hpp>
#include <irondust/util/glm_ostream.hpp>

#include <exception>
#include <sstream>
#include <stdexcept>


namespace irondust
{
    namespace gl
    {
        /**
         * @brief Texture3D::load
         * @param image
         * @return
         */
        Texture3D* Texture3D::load(Image* image)
        {
            if(image->getDepth() <= 1) {
                LOG_ERROR << "can only handle 3D Images, but "
                            << image->getName()
                            << " has a depth of "
                            << image->getDepth()
                            << std::endl;

                return NULL;
            }

            GLuint textureId;
            glGenTextures(1, &textureId);
            Texture3D* tex = new Texture3D(image->getName(), image->getDimensions(), textureId, image->getFormat());
            tex->bind();

            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
            // Set texture interpolation method to use linear interpolation (no MIPMAPS)
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glTexImage3D(GL_TEXTURE_3D,
                    0,		 //mip map level 0..top
                    GL_RGBA, //internal format of the data in memory
                    image->getWidth(),
                    image->getHeight(),
                    image->getDepth(),
                    0,					//border width in pixels (can either be 1 or 0)
                    image->getFormat(), // Image format (i.e. RGB, RGBA, BGR etc.)
                    image->getType(),   // Image data type
                    image->getData());  // The actual image data itself

            tex->unbind();
            LOG_DEBUG << "loaded texture: " << image->getName() << image->getDimensions() << std::endl;
            LOG_GL_ERRORS();
            return tex;
        }


        /**
         * @brief Texture3D::Texture3D
         * @param name
         * @param dim
         * @param textureId
         * @param format
         */
        Texture3D::Texture3D(const std::string& name, const glm::uvec3& dim, const GLuint textureId, GLint format)
            : Texture(name, textureId, format, GL_TEXTURE_3D)
            , dim(dim)
        {
        }


        Texture3D::~Texture3D() {}


        /**
         * @brief Texture3D::render
         */
        void Texture3D::render()
        {
            //TODO check that later!
            LOG_WARN << "Texture3D: rendering not implemented!" << std::endl;
        }
    }
}
