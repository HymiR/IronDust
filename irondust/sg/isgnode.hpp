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


#ifndef ISGNODE_HPP
#define ISGNODE_HPP

#include <irondust/sg/isgelement.hpp>


namespace irondust
{
    namespace sg
    {
        class SGContext;

        class ISGNode : public ISGElement
        {
        public:
            virtual ~ISGNode() = default;

            virtual ISGNode& append(ISGNode* child) = 0;
            virtual bool remove(ISGNode* child) = 0;
        };
    }
}


#endif // ISGNODE_HPP
