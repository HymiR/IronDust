// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 13.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


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
