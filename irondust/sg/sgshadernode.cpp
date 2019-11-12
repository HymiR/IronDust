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


#include <irondust/sg/sgshadernode.hpp>
#include <irondust/sg/sgcontext.hpp>

#include <irondust/gl/GLSLProgram.hpp>


namespace irondust
{
    namespace sg
    {
        SGShaderNode::SGShaderNode(gl::GLSLProgram* program, const std::initializer_list<ISGNode*>& children)
            : base(children)
            , program(program)
        {
        }

        SGShaderNode::SGShaderNode(gl::GLSLProgram* program, ISGNode* child)
            : base(child)
            , program(program)
        {
        }

        SGShaderNode::SGShaderNode(gl::GLSLProgram* program)
            : base()
            , program(program)
        {
        }

        SGShaderNode::~SGShaderNode()
        {
            delete program;
        }

        void SGShaderNode::render(SGContext& context)
        {
            gl::GLSLProgram* backup = context.program;
            context.program = this->program;

            program->bind();
            base::render(context);
            program->unbind();
            context.program = backup;
            if(backup) backup->bind();
        }
    }
}
