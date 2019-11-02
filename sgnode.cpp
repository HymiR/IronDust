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
        : children(nullptr)
        , single(true)
    {
    }

    SGNode::SGNode(const std::vector<ISGNode*>& children)
        : children(new std::vector<ISGNode*>(children))
        , single(false)
    {
    }

    SGNode::SGNode(const std::initializer_list<ISGNode*>& children)
        : children(new std::vector<ISGNode*>(children))
        , single(false)
    {
    }

    SGNode::SGNode(ISGNode* child)
        : children(child)
        , single(true)
    {
    }

    SGNode::~SGNode()
    {
        if(!single) {
            for (ISGNode* child : *reinterpret_cast<std::vector<ISGNode*>*>(children)) delete child;
            delete reinterpret_cast<std::vector<ISGNode*>*>(children);
        }

        delete reinterpret_cast<ISGNode*>(children);
    }

    ISGNode& SGNode::append(ISGNode* child)
    {
        if(!children) {
            this->children = child;
        } else if(single) {
            std::vector<ISGNode*>* c = new std::vector<ISGNode*>();
            c->push_back(reinterpret_cast<ISGNode*>(children));
            c->push_back(reinterpret_cast<ISGNode*>(child));
            children = c;
            single = false;
        } else {
            reinterpret_cast<std::vector<ISGNode*>*>(children)->push_back(child);
        }

        return *child;
    }

    bool SGNode::remove(ISGNode* child)
    {
        if(children) {
            if(single) {
                children = nullptr;
                return true;
            } else {
                auto& children = *reinterpret_cast<std::vector<ISGNode*>*>(this->children);
                auto rem = std::find(children.begin(), children.end(), child);
                if(rem != children.end()) {
                    children.erase(rem);
                    return true;
                }
            }
        }

        return false;
    }

    void SGNode::render(SGContext& context)
    {
        if(single && children) {
            reinterpret_cast<ISGNode*>(children)->render(context);
        } else if(children) {
            for (ISGNode* child : *reinterpret_cast<std::vector<ISGNode*>*>(children)) {
                child->render(context);
            }
        }
    }
}
