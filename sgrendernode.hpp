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


#ifndef SGRENDERNODE_HPP
#define SGRENDERNODE_HPP


#include <isgresourcenode.hpp>

#include <glm/fwd.hpp>

#include <vector>


namespace cg
{
    class SGRenderNode : public ISGResourceNode
    {
        typedef ISGResourceNode base;
        friend class SGModel;

    public:
        std::vector<glm::f32> vertex;
        std::vector<glm::f32> texture;
        std::vector<glm::f32> color;
        std::vector<glm::f32> normal;
        std::vector<glm::uint> index; // uint and u32 may not be the same!

        SGRenderNode(SGContext& context);
        virtual ~SGRenderNode() override;

        // ISGNode interface
        virtual void render(SGContext& context) override;

        // ISGResource interface
        virtual bool init(SGContext& context) override;

    private:
        glm::uint id_vertex;
        glm::uint id_texture;
        glm::uint id_color;
        glm::uint id_normal;
        glm::uint id_index;

        glm::uint items;
        glm::u8 grouping;
    };
}

#endif // SGRENDERNODE_HPP
