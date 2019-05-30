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


#ifndef SGTRANSFORMNODE_HPP
#define SGTRANSFORMNODE_HPP

#include <sgnode.hpp>

#include <glm/mat4x4.hpp>

#include<initializer_list>


namespace cg
{
    class SGTransformNode : public SGNode
    {
        typedef SGNode base;

    public:
        SGTransformNode(const glm::mat4& matrix, const std::initializer_list<ISGNode*>& children={});

        // ISGNode interface
        virtual void render(SGContext& context) override;

    protected:
        glm::mat4 matrix;
    };
}

#endif // SGTRANSFORMNODE_HPP
