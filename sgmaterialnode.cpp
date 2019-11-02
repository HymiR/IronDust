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


#include <sgmaterialnode.hpp>
#include <sgcontext.hpp>
#include <sgconstants.hpp>

#include <initializer_list>


namespace cg
{
    SGMaterialNode::SGMaterialNode(const std::initializer_list<ISGNode*>& children)
        : base(children)
        , ambient(.2, .2, .5, 1)
        , diffuse(.4, .4, 1., 1)
        , specular(.2, .2, .2, 1)
        , emission(0, 0, 0, 1)
        , shininess(30.f)
    {
    }

    SGMaterialNode::SGMaterialNode(ISGNode* child)
        :base(child)
        , ambient(.2, .2, .5, 1)
        , diffuse(.4, .4, 1., 1)
        , specular(.2, .2, .2, 1)
        , emission(0, 0, 0, 1)
        , shininess(30.f)
    {
    }

    SGMaterialNode::SGMaterialNode()
        :base()
        , ambient(.2, .2, .5, 1)
        , diffuse(.4, .4, 1., 1)
        , specular(.2, .2, .2, 1)
        , emission(0, 0, 0, 1)
        , shininess(30.f)
    {
    }

    void SGMaterialNode::render(cg::SGContext& context)
    {
        oogl::GLSLProgram& program = *context.program;
        program[uniform::MATERIAL_AMBIENT] = ambient;
        program[uniform::MATERIAL_DIFFUSE] = diffuse;
        program[uniform::MATERIAL_SPECULAR] = specular;
        program[uniform::MATERIAL_EMISSION] = emission;
        program[uniform::MATERIAL_SHININESS] = shininess;
        base::render(context);
    }
}
