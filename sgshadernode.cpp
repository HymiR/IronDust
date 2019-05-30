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


#include <sgshadernode.hpp>
#include <sgcontext.hpp>

#include <cg/oogl/GLSLProgram.hpp>


namespace cg
{

    SGShaderNode::SGShaderNode(oogl::GLSLProgram* program, const std::initializer_list<ISGNode*>& children)
        : base(children)
        , program(program)
    {
    }

    SGShaderNode::~SGShaderNode()
    {
        delete program;
    }

    void SGShaderNode::render(SGContext& context)
    {
        oogl::GLSLProgram* backup = context.program;
        context.program = this->program;

        program->bind();
        base::render(context);
        program->unbind();
        context.program = backup;
        if(backup) backup->bind();
    }
}
