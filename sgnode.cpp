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


#include <sgnode.hpp>

#include <algorithm>


namespace cg
{

    SGNode::SGNode()
    {
    }

    SGNode::SGNode(const std::vector<ISGNode*>& children)
        :children(children)
    {
    }

    SGNode::SGNode(const std::initializer_list<ISGNode*>& children)
        :children(children)
    {
    }

    SGNode::SGNode(ISGNode* child)
        :children({child})
    {
    }

    SGNode::~SGNode()
    {
        for (ISGNode* child : children)
            delete child;

        children.clear();
    }

    ISGNode& SGNode::append(ISGNode* child)
    {
        children.push_back(child);
        return *children.back();
    }

    bool SGNode::remove(ISGNode* child)
    {
        auto rem = std::find(children.begin(), children.end(), child);
        if(rem != children.end()) {
            children.erase(rem);
            return true;
        }

        return false;
    }

    void SGNode::render(SGContext& context)
    {
        for (ISGNode* child : children) {
            child->render(context);
        }
    }
}
