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


#ifndef SGTEXTURENODE_HPP
#define SGTEXTURENODE_HPP

#include <isgresourcenode.hpp>

#include <glm/fwd.hpp>

#include <string>


namespace cg
{
    namespace oogl
    {
        class Image;
    }

    class SGTextureNode : public ISGResourceNode
    {
        typedef ISGResourceNode base;

    public:
        SGTextureNode(SGContext& context, oogl::Image* image, bool repeat=false, const std::initializer_list<ISGNode*>& children = {});
        SGTextureNode(SGContext& context, const std::string& path, bool repeat=false, const std::initializer_list<ISGNode*>& children = {});
        virtual ~SGTextureNode() override;

        virtual bool init(SGContext& context) override;
        virtual void render(SGContext& context) override;

    protected:
        virtual void bind();
        virtual void unbind();

    private:
        oogl::Image* image;
        bool repeat;
        glm::uint id;

        // this MUST be an int rather than uint.
        int unit;
    };
}

#endif // SGTEXTURENODE_HPP
