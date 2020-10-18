/**
 ** This file is part of the irondust project.
 ** Copyright 2020 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
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


#include <irondust/sg/sgcubemapnode.hpp>
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
//        SGCubemapNode::SGCubemapNode(SGContext& context, const std::array<gl::Image*, 6>& faces, bool reflect)
//            : base(context)
//            , faces(faces)
//            , id(0)
//            , unit(0)
//            , reflect(reflect)
//        {
//        }

        SGCubemapNode::SGCubemapNode(SGContext& context, const std::array<std::string, 6>& f, bool reflect)
            : base(context)
            , faces{Image::shared(f[0]), Image::shared(f[1]), Image::shared(f[2]), Image::shared(f[3]),Image::shared(f[4]),Image::shared(f[5])}
            , id(0)
            , unit(0)
            , reflect(reflect)
        {
        }

        SGCubemapNode::SGCubemapNode(SGContext& context, const SGCubemapNode* other)
            : base(context)
            , faces(other->faces)
            , id(0)
            , unit(0)
            , reflect(true)
        {
        }

        SGCubemapNode::~SGCubemapNode()
        {
            //for(auto* f : faces) delete f;
        }

        bool SGCubemapNode::init(SGContext& context)
        {
            static const GLenum targets[6] {
                GL_TEXTURE_CUBE_MAP_POSITIVE_X, // right
                GL_TEXTURE_CUBE_MAP_NEGATIVE_X, // left
                GL_TEXTURE_CUBE_MAP_POSITIVE_Z, // front?
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, // back?
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, // up?
                GL_TEXTURE_CUBE_MAP_POSITIVE_Y, // down?
            };

            static_cast<void>(context);
            bool success = true;

            glGenTextures(1, &id);
            bind();

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP); // optional

            for(glm::u8 i = 0; i < 6; i++) {
                if(faces[i] == nullptr) {
                    success = false;
                    break;
                }
                glTexImage2D(targets[i], 0, GL_RGBA,
                            static_cast<GLsizei>(faces[i]->getWidth()),
                            static_cast<GLsizei>(faces[i]->getHeight()),
                            0,
                            faces[i]->getFormat(),
                            faces[i]->getType(),
                            faces[i]->getData());
            }
            unbind();
            return success;
        }

        void SGCubemapNode::render(SGContext& context)
        {
            auto& program = *context.program;
            program[uniform::OPTIONS_REFLECT] = reflect;
            program[uniform::TEX_OBJ_CUBE] = unit;
            glm::mat3 invview_matrix =  glm::mat3(glm::inverse(context.view_matrix));
            program[uniform::MAT_INVVIEW] = invview_matrix;

            bind();
            base::render(context);

            program[uniform::OPTIONS_REFLECT] = false;
            unbind();
        }

        void SGCubemapNode::bind()
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        }

        void SGCubemapNode::unbind()
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_CUBE_MAP, GL_NONE);
        }
    }
}
