/*
 * gl_error.cpp
 *
 *  Created on: 14.02.2011
 *      Author: sam
 */


#include <irondust/gl/gl_error.hpp>


namespace irondust
{
    namespace gl
    {
        const char* glErrorStr(GLenum err)
        {
            switch (err)
            {
                case GL_NO_ERROR:                      return "GL_NO_ERROR";
                case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
                case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
                case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
                case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
                case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
                case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
                case 0x8031: /* not core */            return "GL_TABLE_TOO_LARGE_EXT";
                case 0x8065: /* not core */            return "GL_TEXTURE_TOO_LARGE_EXT";
                case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
                default:
                    LOG_ERROR << "Unhandled GL error code" << std::endl;
                    return nullptr;
            }
        }

        /**
         * @brief dumpGLInfos
         */
        void dumpGLInfos()
        {
            if(!LOG_IS_INFO_ENABLED)
                return;

            if(glGetString(GL_SHADING_LANGUAGE_VERSION)) {
                LOG_INFO << std::endl
                         << "Vendor: " << glGetString(GL_VENDOR) << std::endl
                         << "Renderer: " << glGetString(GL_RENDERER) << std::endl
                         << "Version: " << glGetString(GL_VERSION) << std::endl
                         << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            } else {
                LOG_INFO << std::endl
                         << "Vendor: " << glGetString(GL_VENDOR) << std::endl
                         << "Renderer: " << glGetString(GL_RENDERER) << std::endl
                         << "Version: " << glGetString(GL_VERSION) << std::endl
                         << "GLSL Version: "
                         << "UNKNOWN" << std::endl;
            }

            LOG_DEBUG << std::endl
                        << "Extensions: " << glGetString(GL_EXTENSIONS) << std::endl;
        }
    }
}
