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
