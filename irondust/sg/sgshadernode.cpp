/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


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
