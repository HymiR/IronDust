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


#include <irondust/sg/sglightnode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgconstants.hpp>


namespace irondust
{
    namespace sg
    {
        SGLightNode::SGLightNode(ISGNode* child, glm::vec3 position)
            : base(child)
            , ambient(0.5, 0.5, 0.5, 1)
            , diffuse(1, 1, 1, 1)
            , specular(1, 1, 1, 1)
            , position(position)
        {
        }

        SGLightNode::SGLightNode(glm::vec3 position)
            : base()
            , ambient(0.5, 0.5, 0.5, 1)
            , diffuse(1, 1, 1, 1)
            , specular(1, 1, 1, 1)
            , position(position)
        {
        }

        void SGLightNode::render(SGContext& context)
        {
            static glm::vec4 worldpos = glm::vec4(position, 1) * context.view_matrix * context.scene_matrix;
            auto& program = *context.program;

            program[uniform::LIGHT_AMBIENT] = ambient;
            program[uniform::LIGHT_DIFFUSE] = diffuse;
            program[uniform::LIGHT_SPECULAR] = specular;
            program[uniform::LIGHT_POS] = glm::vec3(worldpos);

            base::render(context);
        }
    }
}
