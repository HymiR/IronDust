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


#include <irondust/sg/sglightnode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgconstants.hpp>


namespace irondust
{
    namespace sg
    {
        SGLightNode::SGLightNode(ISGNode* child, glm::vec3 position)
            : base(child)
            , ambient(0.5, 0.5, 0.5, 1)
            , diffuse(1, 1, 1, 1)
            , specular(1, 1, 1, 1)
            , position(position)
        {
        }

        SGLightNode::SGLightNode(glm::vec3 position)
            : base()
            , ambient(0.5, 0.5, 0.5, 1)
            , diffuse(1, 1, 1, 1)
            , specular(1, 1, 1, 1)
            , position(position)
        {
        }

        void SGLightNode::render(SGContext& context)
        {
            static glm::vec4 worldpos = glm::vec4(position, 1) * context.view_matrix * context.scene_matrix;
            auto& program = *context.program;

            program[uniform::LIGHT_AMBIENT] = ambient;
            program[uniform::LIGHT_DIFFUSE] = diffuse;
            program[uniform::LIGHT_SPECULAR] = specular;
            program[uniform::LIGHT_POS] = glm::vec3(worldpos);

            base::render(context);
        }
    }
}
