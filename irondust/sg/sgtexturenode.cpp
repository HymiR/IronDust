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


#include <irondust/sg/sgtexturenode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgconstants.hpp>

#include <irondust/gl/Image.hpp>
#include <irondust/gl/glIncludes.hpp>

#include <glm/glm.hpp>


using namespace irondust::gl;


namespace irondust
{
    namespace sg
    {
        SGTextureNode::SGTextureNode(SGContext& context, gl::Image* image, const std::initializer_list<ISGNode*>& children, bool repeat)
            : base(context, children)
            , image(image)
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }

        SGTextureNode::SGTextureNode(SGContext& context, const std::string& path, const std::initializer_list<ISGNode*>& children, bool repeat)
            : base(context, children)
            , image(Image::load(path))
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }

        SGTextureNode::SGTextureNode(SGContext& context, Image* image, ISGNode* child, bool repeat)
            : base(context, child)
            , image(image)
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }

        SGTextureNode::SGTextureNode(SGContext& context, const std::string& path, ISGNode* child, bool repeat)
            : base(context, child)
            , image(Image::load(path))
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }

        SGTextureNode::SGTextureNode(SGContext& context, Image* image, bool repeat)
            : base(context)
            , image(image)
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }

        SGTextureNode::SGTextureNode(SGContext& context, const std::string& path, bool repeat)
            : base(context)
            , image(Image::load(path))
            , repeat(repeat)
            , id(0)
            , unit(0)
        {
        }


        SGTextureNode::~SGTextureNode()
        {
            delete image;
            image = nullptr;
        }

        bool SGTextureNode::init(SGContext& context)
        {
            static_cast<void>(context);
            if(image == nullptr) return false;
            int mode = repeat? GL_REPEAT : GL_CLAMP;

            glGenTextures(1, &id);
            bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
            // Set texture interpolation method to use linear interpolation (no MIPMAPS)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0,
                        GL_RGBA,
                        static_cast<GLsizei>(image->getWidth()),
                        static_cast<GLsizei>(image->getHeight()),
                        0,
                        image->getFormat(),
                        image->getType(),
                        image->getData());

            unbind();
            return true;
        }

        void SGTextureNode::render(SGContext& context)
        {
            auto& program = *context.program;
            program[uniform::OPTIONS + "[0]"] = true;
            program[uniform::TEX_OBJECT] = unit;

            bind();
            base::render(context);

            program[uniform::OPTIONS + "[0]"] = false;
            unbind();
        }

        void SGTextureNode::bind()
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void SGTextureNode::unbind()
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, GL_NONE);
        }
    }
}
