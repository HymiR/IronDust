// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 12.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#ifndef SGCONTEXT_HPP
#define SGCONTEXT_HPP


#include <glm/glm.hpp>

#include <irondust/gl/GLSLProgram.hpp>


namespace irondust
{
    namespace sg
    {
        class SGScene;

        class SGContext
        {
        public:
            SGContext(SGScene& scene);
            virtual ~SGContext();

            gl::GLSLProgram* program;
            SGScene& scene;

            glm::mat4 scene_matrix;
            glm::mat4 view_matrix;
            glm::mat4 projection_matrix;
        };
    }
}


#endif // SGCONTEXT_HPP
