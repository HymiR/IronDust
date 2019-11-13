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


#include <irondust/sg/sgtransformnode.hpp>
#include <irondust/sg/sgcontext.hpp>


namespace irondust
{
    namespace sg
    {
        SGTransformNode::SGTransformNode(const glm::mat4& matrix, const std::initializer_list<ISGNode*>& children)
            : base(children)
            , matrix(matrix)
        {
        }

        void SGTransformNode::render(SGContext& context)
        {
            glm::mat4 backup = context.scene_matrix;
            context.scene_matrix *= matrix;
            base::render(context);
            context.scene_matrix = backup;
        }
    }
}
