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


#include <irondust/sg/sgrendernode.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgconstants.hpp>

#include <irondust/gl/glIncludes.hpp>
#include <irondust/gl/iglbindable.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

// debugging stuff
#include <cassert>


template<typename T> std::size_t bytesof(const std::vector<T>& v)
{
    return v.size() * sizeof (T);
}

template<typename T, uint S> std::size_t bytesof()
{
    return S * sizeof (T);
}


namespace irondust
{
    namespace sg
    {
        SGRenderNode::SGRenderNode(SGContext& context)
            : base(context)
            , id_vertex(0)
            , id_texture(0)
            , id_color(0)
            , id_normal(0)
            , id_index(0)
            , items(0)
            , grouping(3)
        {
        }

        SGRenderNode::~SGRenderNode()
        {
            glDeleteBuffers(1, &id_vertex);
            glDeleteBuffers(1, &id_texture);
            glDeleteBuffers(1, &id_color);
            glDeleteBuffers(1, &id_normal);
            glDeleteBuffers(1, &id_index);
            for(auto* opt : options) delete opt;
        }

        void SGRenderNode::render(SGContext& context)
        {
            assert(context.program && (id_vertex != 0));
            for(auto* opt : options) opt->bind();

            glm::mat4 mvMat = context.view_matrix * context.scene_matrix;
            glm::mat3 normalMat = glm::inverseTranspose(glm::mat3(mvMat));
            auto& program = *context.program;

            auto uniform = program[uniform::MAT_NORMAL];
            if(uniform) uniform = normalMat;
            program[uniform::MAT_MODELVIEW] = mvMat;
            program[uniform::MAT_PROJ] = context.projection_matrix;

            auto pid = context.program->getId();

            // do render stuff here
            auto pos_vertex = glGetAttribLocation(pid, attrib::VERTEX.c_str());
            assert(pos_vertex >= 0);
            glEnableVertexAttribArray(pos_vertex);
            glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
            glVertexAttribPointer(pos_vertex, grouping, GL_FLOAT, GL_FALSE, 0, nullptr);

            glm::int32 pos_texture = -1;
            if(id_texture != 0) {
                pos_texture = glGetAttribLocation(pid, attrib::TEXTURE.c_str());
                if (pos_texture >= 0) {
                    glEnableVertexAttribArray(pos_texture);
                    glBindBuffer(GL_ARRAY_BUFFER, id_texture);
                    glVertexAttribPointer(pos_texture, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                }
            }

            glm::int32 pos_color = -1;
            if(id_color != 0) {
                pos_color = glGetAttribLocation(pid, attrib::COLOR.c_str());
                if (pos_color >= 0) {
                    glEnableVertexAttribArray(pos_color);
                    glBindBuffer(GL_ARRAY_BUFFER, id_color);
                    glVertexAttribPointer(pos_color, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
                }
            }

            glm::int32 pos_normal = -1;
            if(id_normal != 0) {
                pos_normal = glGetAttribLocation(pid, attrib::NORMAL.c_str());
                if (pos_normal >= 0) {
                    glEnableVertexAttribArray(pos_normal);
                    glBindBuffer(GL_ARRAY_BUFFER, id_normal);
                    glVertexAttribPointer(pos_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                }
            }

            if(id_index != 0) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
                glDrawElements(GL_TRIANGLES, GLsizei(items), GL_UNSIGNED_INT, nullptr);
            } else {
                glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
                glDrawArrays(GL_TRIANGLES, 0, GLsizei(items));
            }

            if(pos_texture >= 0) glDisableVertexAttribArray(pos_texture);
            if(pos_color >= 0) glDisableVertexAttribArray(pos_color);
            if(pos_normal >= 0) glDisableVertexAttribArray(pos_normal);
            if(pos_vertex >= 0) glDisableVertexAttribArray(pos_vertex);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            base::render(context);

            for(auto* opt : options) opt->unbind();
        }

        bool SGRenderNode::init(SGContext& context)
        {
            static_cast<void>(context);
            if(vertex.empty()) return false;
            if(!index.empty()) items = glm::uint(index.size());
            else items = glm::uint(vertex.size() / grouping);

            glGenBuffers(1, &id_vertex);
            glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
            glBufferData(GL_ARRAY_BUFFER, bytesof(vertex), vertex.data(), GL_STATIC_DRAW);
            //vertex.clear();

            if(!texture.empty()) {
                glGenBuffers(1, &id_texture);
                glBindBuffer(GL_ARRAY_BUFFER, id_texture);
                glBufferData(GL_ARRAY_BUFFER, bytesof(texture), texture.data(), GL_STATIC_DRAW);
                //texture.clear();
            }

            if(!color.empty()) {
                glGenBuffers(1, &id_color);
                glBindBuffer(GL_ARRAY_BUFFER, id_color);
                glBufferData(GL_ARRAY_BUFFER, bytesof(color), color.data(), GL_STATIC_DRAW);
                //color.clear();
            }

            if(!normal.empty()) {
                glGenBuffers(1, &id_normal);
                glBindBuffer(GL_ARRAY_BUFFER, id_normal);
                glBufferData(GL_ARRAY_BUFFER, bytesof(normal), normal.data(), GL_STATIC_DRAW);
                //normal.clear();
            }

            if(!index.empty()) {
                glGenBuffers(1, &id_index);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesof(index), index.data(), GL_STATIC_DRAW);
                //index.clear();
            }

            // unbind buffers when finished
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            return true;
        }
    }
}
