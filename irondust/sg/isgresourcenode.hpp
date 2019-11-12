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


#ifndef ISGRESOURCENODE_HPP
#define ISGRESOURCENODE_HPP

#include <irondust/sg/sgnode.hpp>
#include <irondust/sg/isgresource.hpp>


namespace irondust
{
    namespace sg
    {
        class ISGResourceNode : public SGNode, public ISGResource
        {
            typedef SGNode base;

        public:
            ISGResourceNode(SGContext& context, const std::initializer_list<ISGNode*>& children);
            ISGResourceNode(SGContext& context, ISGNode* child);
            ISGResourceNode(SGContext& context);
        };
    }
}


#endif // ISGRESOURCENODE_HPP
