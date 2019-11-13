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


#include <irondust/sg/sgnode.hpp>

#include <algorithm>


namespace irondust
{
    namespace sg
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
}
