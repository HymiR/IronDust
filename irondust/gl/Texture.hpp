/*
 * Texture.hpp
 *
 *  Created on: 12.07.2010
 *      Author: sam
 */


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <irondust/util/log.hpp>
#include <irondust/gl/glIncludes.hpp>

#include <glm/fwd.hpp>

#include <utility>
#include <memory>


namespace irondust
{
    namespace gl
    {
        /**
         * @brief The Texture class
         */
        class Texture
        {
        public:
            virtual ~Texture();


            GLint getFormat()
            {
                return format;
            }


            std::string getName() const
            {
                return name;
            }

            GLuint getID()
            {
                return textureId;
            }

            int getBindedTexture()
            {
                return bindedTexture;
            }

            virtual void bind(glm::uint toTexture = 0);
            virtual void unbind();

            virtual void render() = 0;

        protected:
            friend class GLSLAttrib;
            friend class FrameBufferObject;

            Texture(const std::string& name, const GLuint textureId, GLint format, GLenum textureType);

            bool isBound() const
            {
                return bindedTexture >= 0;
            }

        private:
            std::string name;
            GLuint textureId;
            GLint format;
            GLenum textureType;
            int bindedTexture;
        };

        Texture* loadTexture(const std::string& fileName);
    }
}


#endif // TEXTURE_HPP
