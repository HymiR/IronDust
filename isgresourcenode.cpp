// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 14.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#include <isgresourcenode.hpp>
#include <sgcontext.hpp>
#include <sgscene.hpp>


namespace cg
{
    ISGResourceNode::ISGResourceNode(SGContext& context, const std::initializer_list<ISGNode*>& children)
        :base(children)
    {
        context.scene.record(this);
    }
}
