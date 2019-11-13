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


#include <irondust/sg/sgmaterialnode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgconstants.hpp>

#include <initializer_list>


namespace irondust
{
    namespace sg
    {
        SGMaterialNode::SGMaterialNode(const std::initializer_list<ISGNode*>& children)
            : base(children)
            , ambient(.2, .2, .5, 1)
            , diffuse(.4, .4, 1., 1)
            , specular(.2, .2, .2, 1)
            , emission(0, 0, 0, 1)
            , shininess(30.f)
        {
        }

        SGMaterialNode::SGMaterialNode(ISGNode* child)
            :base(child)
            , ambient(.2, .2, .5, 1)
            , diffuse(.4, .4, 1., 1)
            , specular(.2, .2, .2, 1)
            , emission(0, 0, 0, 1)
            , shininess(30.f)
        {
        }

        SGMaterialNode::SGMaterialNode()
            :base()
            , ambient(.2, .2, .5, 1)
            , diffuse(.4, .4, 1., 1)
            , specular(.2, .2, .2, 1)
            , emission(0, 0, 0, 1)
            , shininess(30.f)
        {
        }

        void SGMaterialNode::render(SGContext& context)
        {
            gl::GLSLProgram& program = *context.program;
            program[uniform::MATERIAL_AMBIENT] = ambient;
            program[uniform::MATERIAL_DIFFUSE] = diffuse;
            program[uniform::MATERIAL_SPECULAR] = specular;
            program[uniform::MATERIAL_EMISSION] = emission;
            program[uniform::MATERIAL_SHININESS] = shininess;
            base::render(context);
        }
    }
}
