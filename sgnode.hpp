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


#ifndef SGNODE_HPP
#define SGNODE_HPP

#include <isgnode.hpp>

#include <vector>
#include <initializer_list>

namespace cg
{
    class SGNode : public ISGNode
    {
    public:
        SGNode();
        SGNode(const std::vector<ISGNode*>& children);
        SGNode(const std::initializer_list<ISGNode*>& children);
        SGNode(ISGNode* child);

        virtual ~SGNode() override;

        virtual ISGNode& append(ISGNode* node) override;
        virtual bool remove(ISGNode* node) override;
        virtual void render(SGContext& context) override;

    private:
        std::vector<ISGNode*> children;
    };
}

#endif // SGNODE_HPP
