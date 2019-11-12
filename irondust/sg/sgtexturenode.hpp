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

#include <irondust/sg/isgresourcenode.hpp>

#include <glm/fwd.hpp>

#include <string>


namespace irondust
{
    namespace gl
    {
        class Image;
    }

    namespace sg
    {
        class SGTextureNode : public ISGResourceNode
        {
            typedef ISGResourceNode base;

        public:
            SGTextureNode(SGContext& context, gl::Image* image, const std::initializer_list<ISGNode*>& children, bool repeat=false);
            SGTextureNode(SGContext& context, const std::string& path, const std::initializer_list<ISGNode*>& children, bool repeat=false);
            SGTextureNode(SGContext& context, gl::Image* image, ISGNode* child, bool repeat=false);
            SGTextureNode(SGContext& context, const std::string& path, ISGNode* child, bool repeat=false);
            SGTextureNode(SGContext& context, gl::Image* image, bool repeat=false);
            SGTextureNode(SGContext& context, const std::string& path, bool repeat=false);

            virtual ~SGTextureNode() override;

            virtual bool init(SGContext& context) override;
            virtual void render(SGContext& context) override;

        protected:
            virtual void bind();
            virtual void unbind();

        private:
            gl::Image* image;
            bool repeat;
            glm::uint id;

            // this MUST be an int rather than uint.
            int unit;
        };
    }
}

#endif // SGTEXTURENODE_HPP
