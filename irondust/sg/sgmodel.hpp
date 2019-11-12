// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 15.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#ifndef SGMODEL_HPP
#define SGMODEL_HPP

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace irondust
{
    namespace sg
    {
        class ISGNode;
        class SGContext;


        class SGModel
        {
        public:
            static ISGNode* createSphere(SGContext& context, glm::f32 radius=2.f, glm::uvec2 grid={30, 30});
            static ISGNode* createPyramid(SGContext& context, glm::f32 s=1.0f, glm::f32 h=0.75f);
            static ISGNode* createCube(SGContext& context, glm::vec3 size={1.f, 1.f, 1.f});
            static ISGNode* createQuad(SGContext& context, glm::vec2 size={2.f, 2.f});

        protected:
            SGModel();
        };
    }
}
#endif // SGMODEL_HPP
