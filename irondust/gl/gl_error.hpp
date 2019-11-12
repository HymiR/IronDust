/*
 * gl_error.hpp
 *
 *  Created on: 10.02.2011
 *      Author: sam
 */


#ifndef GL_ERROR_HPP
#define GL_ERROR_HPP

#include <irondust/util/log.hpp>
#include <irondust/gl/glIncludes.hpp>


#define LOG_GL_ERRORS()                                                          \
    {                                                                            \
        for(GLenum err = glGetError(); err != GL_NO_ERROR; err = glGetError()) { \
            LOG_ERROR << "GL_ERROR: " << err << std::endl;       \
        }                                                                        \
    }

namespace irondust
{
    namespace gl
    {
        void dumpGLInfos();
    }
}


#endif // GL_ERROR_HPP
