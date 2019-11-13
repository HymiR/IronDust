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


#include <irondust/sg/isgresourcenode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgscene.hpp>


namespace irondust
{
    namespace sg
    {
        // TODO shouldn't this class also unrecord it selve on destruction?
        ISGResourceNode::ISGResourceNode(SGContext& context, const std::initializer_list<ISGNode*>& children)
            : base(children)
        {
            context.scene.record(this);
        }

        ISGResourceNode::ISGResourceNode(SGContext& context, ISGNode* child)
            : base(child)
        {
            context.scene.record(this);
        }

        ISGResourceNode::ISGResourceNode(SGContext& context)
            : base()
        {
            context.scene.record(this);
        }
    }
}
