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


#ifndef SGLIGHTNODE_HPP
#define SGLIGHTNODE_HPP

#include <irondust/sg/sgnode.hpp>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>


namespace irondust
{
    namespace sg
    {
        class SGLightNode : public SGNode
        {
            typedef SGNode base;

        public:
            glm::vec4 ambient;
            glm::vec4 diffuse;
            glm::vec4 specular;

            SGLightNode(ISGNode* child, glm::vec3 position=glm::vec3(0, 0, 0));
            SGLightNode(glm::vec3 position=glm::vec3(0, 0, 0));

            // ISGNode interface
            virtual void render(SGContext& context) override;

        private:
            glm::vec3 position;
        };
    }
}

#endif // SGLIGHTNODE_HPP
