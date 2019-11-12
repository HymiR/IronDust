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


#ifndef SGSHADERNODE_HPP
#define SGSHADERNODE_HPP

#include <irondust/sg/sgnode.hpp>

#include <initializer_list>


namespace irondust
{
    namespace gl
    {
        class GLSLProgram;
    }

    namespace sg
    {


        class SGShaderNode : public SGNode
        {
            typedef SGNode base;

        public:
            SGShaderNode(gl::GLSLProgram* program, const std::initializer_list<ISGNode*>& children);
            SGShaderNode(gl::GLSLProgram* program, ISGNode* child);
            SGShaderNode(gl::GLSLProgram* program);

            virtual ~SGShaderNode() override;
            virtual void render(SGContext& context) override;

        private:
            gl::GLSLProgram* program;
        };
    }
}

#endif // SGSHADERNODE_HPP
