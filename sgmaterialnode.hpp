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


#ifndef SGMATERIALNODE_HPP
#define SGMATERIALNODE_HPP

#include <sgnode.hpp>
#include <glm/vec4.hpp>
#include <glm/fwd.hpp>


namespace cg
{
    class SGMaterialNode : public SGNode
    {
        typedef SGNode base;

    public:
        SGMaterialNode(const std::initializer_list<ISGNode*>& children={});

        // ISGNode interface
        virtual void render(SGContext& context) override;

        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 emission;
        glm::f32 shininess;
    };
}

#endif // SGMATERIALNODE_HPP
