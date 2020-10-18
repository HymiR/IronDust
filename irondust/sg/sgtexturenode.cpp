/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


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

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
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
            program[uniform::OPTIONS_TEX] = true;
            program[uniform::TEX_OBJ_2D] = unit;

            bind();
            base::render(context);

            program[uniform::OPTIONS_TEX] = false;
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
