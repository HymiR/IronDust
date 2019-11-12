/*
 * GLSLShader.hpp
 *
 *  Created on: 12.07.2010
 *      Author: sam
 */


#ifndef GLSL_SHADER_HPP
#define GLSL_SHADER_HPP

#include <irondust/gl/glIncludes.hpp>

#include <string>

/**
 * TODO following has to be done here:
 * - bool() operator which states validity
 * - streamoperator for string output instead of tostring
 */

namespace irondust
{
    namespace gl
    {
        class GLSLShader
        {
        public:
            enum ShaderType {
                VERTEX = GL_VERTEX_SHADER,
                FRAGMENT = GL_FRAGMENT_SHADER,
                GEOMETRY = GL_GEOMETRY_SHADER_EXT
            };


            virtual ~GLSLShader();
            const char* toString(const ShaderType type) const;

            static GLSLShader* create(const ShaderType shaderType, const std::string& filename);
            static GLSLShader* createFromSource(const ShaderType shaderType, const std::string& code);
            static GLuint load(const ShaderType shaderType, const std::string& filename);

            static std::string getInfoLog(GLuint shaderId);

        private:
            friend class GLSLProgram;
            GLSLShader(const ShaderType shaderType, const std::string& filename, bool isCode=false, bool cleanUpOnFree=true);

            ShaderType type;
            std::string filename;
            bool cleanUpOnFree;
            GLuint shader;

            void loadFromFile(const std::string& filename);
            void load(const std::string& code);
        };

        GLuint loadShader(const std::string& filename, GLenum type);
    }
}


#endif // GLSL_SHADER_HPP
