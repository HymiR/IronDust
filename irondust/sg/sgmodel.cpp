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


#include <irondust/sg/sgmodel.hpp>
#include <irondust/sg/sgrendernode.hpp>
#include <irondust/sg/sgcontext.hpp>

#include <glm/gtc/constants.hpp>
#include <glm/gtx/normal.hpp>

#include <vector>


std::vector<glm::f32>& operator <<(std::vector<glm::f32>& buf, glm::vec3& v)
{
    buf.push_back(v.x);
    buf.push_back(v.y);
    buf.push_back(v.z);
    return buf;
}


namespace irondust
{
    namespace sg
    {
        /**
         * @brief SGModel::createSphere
         * @param context Scene graph context ref.
         * @param radius The radius in units
         * @param grid {latitudes, longitudes} of the sphere
         * @return A render scene graph node.
         */
        ISGNode* SGModel::createSphere(SGContext& context, glm::f32 radius, glm::uvec2 grid)
        {
            auto* node = new SGRenderNode(context);

            for(glm::u16 lat = 0; lat <= grid.x; lat++) {
                glm::f32 theta = static_cast<glm::f32>(lat) * glm::pi<glm::f32>() / grid.x;
                glm::f32 sinTheta = glm::sin(theta);
                glm::f32 cosTheta = glm::cos(theta);

                for(glm::u16 lon=0; lon<= grid.y; lon++) {
                    glm::f32 phi = static_cast<glm::f32>(lon) * glm::pi<glm::f32>() * 2.f / grid.y;
                    glm::f32 sinPhi = glm::sin(phi);
                    glm::f32 cosPhi = glm::cos(phi);
                    glm::f32 x = cosPhi * sinTheta;
                    glm::f32 y = cosTheta;
                    glm::f32 z = sinPhi * sinTheta;
                    glm::f32 u = 1.f - (static_cast<glm::f32>(lon) / grid.y);
                    glm::f32 v = 1.f - (static_cast<glm::f32>(lat) / grid.x);
                    node->normal.push_back(x);
                    node->normal.push_back(y);
                    node->normal.push_back(z);
                    node->texture.push_back(u);
                    node->texture.push_back(v);
                    node->vertex.push_back(x * radius);
                    node->vertex.push_back(y * radius);
                    node->vertex.push_back(z * radius);

                    // create indices:
                    if((lat < grid.x) && (lon < grid.y)) {
                        glm::u32 first = lat * (grid.x + 1u) + lon;
                        glm::u32 second = first + grid.y + 1u;
                        node->index.push_back(first);
                        node->index.push_back(second);
                        node->index.push_back(first + 1u);
                        node->index.push_back(second);
                        node->index.push_back(second + 1u);
                        node->index.push_back(first + 1u);
                    }
                }
            }
            return node;
        }

        ISGNode* SGModel::createPyramid(SGContext& context, glm::f32 s, glm::f32 h)
        {
            glm::f32 hs = s/2.0f;
            glm::f32 n = glm::max(s,h);
            glm::f32 s1 = s/n;
            glm::f32 s2 = 1.0f-s1;
            glm::f32 s3 = s1/2.0f;
            glm::f32 s4 = 1.0f-h/n;
            auto* node = new SGRenderNode(context);

            node->vertex = {
                // floor
               -hs, 0.0,  hs,  // A 0
               -hs, 0.0, -hs,  // B 1
                hs, 0.0, -hs,  // C 2
                hs, 0.0,  hs,  // D 3
                // west
               -hs, 0.0, -hs,  // B 4
               -hs, 0.0,  hs,  // A 5
                0.0, h,   0.0, // E 6
                // south
               -hs, 0.0,  hs,  // A 7
                hs, 0.0,  hs,  // D 8
                0.0, h,   0.0, // E 9
                // east
                hs, 0.0,  hs,  // D 10
                hs, 0.0, -hs,  // C 11
                0.0, h,   0.0, // E 12
                // north
                hs, 0.0, -hs,  // C 13
               -hs, 0.0, -hs,  // B 14
                0.0, h,   0.0, // E 15
            };
            node->index = {
                0,   1,  2,
                2,   3,  0,
                4,   5,  6,
                7,   8,  9,
                10, 11, 12,
                13, 14, 15,
            };
            node->normal = {
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
            };
            {
                auto& v = node->vertex;
                glm::vec3 A(v[0], v[1], v[2]);
                glm::vec3 B(v[3], v[4], v[5]);
                glm::vec3 C(v[6], v[7], v[8]);
                glm::vec3 D(v[9], v[10], v[11]);
                glm::vec3 E(v[18], v[19], v[20]);
                glm::vec3 west =  glm::triangleNormal(B, A, E);
                glm::vec3 south = glm::triangleNormal(A, D, E);
                glm::vec3 east =  glm::triangleNormal(D, C, E);
                glm::vec3 north = glm::triangleNormal(C, B, E);
                node->normal << west << west << west;
                node->normal << south << south << south;
                node->normal << east << east << east;
                node->normal << north << north << north;
            }
            node->texture = {
                0.0,  s2,
                0.0, 1.0,
                 s1, 1.0,
                 s1,  s2,
                0.0, 1.0,
                 s1, 1.0,
                 s3,  s4,
                0.0, 1.0,
                 s1, 1.0,
                 s3,  s4,
                0.0, 1.0,
                 s1, 1.0,
                 s3,  s4,
                0.0, 1.0,
                 s1, 1.0,
                 s3,  s4,
            };

            return node;
        }

        /**
         * @brief SGModel::createCube
         * Each face consists of 2 triangles. On each face, there are two diagonal points
         * which share vertices and normals. So we have 4 distinct vertex-normal combinations per face.
         * @param context Scene graph context ref.
         * @param size {width, height, depth} in units.
         * @return A render scene graph node.
         */
        ISGNode* SGModel::createCube(SGContext& context, glm::vec3 size)
        {
            size = glm::abs(size/2.f);
            auto* node = new SGRenderNode(context);

            node->vertex = {
                // north
                size.x, -size.y, -size.z, // B 0
               -size.x, -size.y, -size.z, // A 1
               -size.x,  size.y, -size.z, // D 2
                size.x,  size.y, -size.z, // C 3
                // west
               -size.x, -size.y, -size.z, // A 4
               -size.x, -size.y,  size.z, // E 5
               -size.x,  size.y,  size.z, // H 6
               -size.x,  size.y, -size.z, // D 7
                // south
               -size.x, -size.y,  size.z, // E 8
                size.x, -size.y,  size.z, // F 9
                size.x,  size.y,  size.z, // G 10
               -size.x,  size.y,  size.z, // H 11
                // east
                size.x, -size.y,  size.z, // F 12
                size.x, -size.y, -size.z, // B 13
                size.x,  size.y, -size.z, // C 14
                size.x,  size.y,  size.z, // G 15
                // top
               -size.x,  size.y,  size.z, // H 16
                size.x,  size.y,  size.z, // G 17
                size.x,  size.y, -size.z, // C 18
               -size.x,  size.y, -size.z, // D 19
                // bottom
               -size.x, -size.y,  size.z, // E 20
               -size.x, -size.y, -size.z, // A 21
                size.x, -size.y, -size.z, // B 22
                size.x, -size.y,  size.z, // F 23
            };
            node->index = {
                 0u,  1u,  2u,   2u,  3u,  0u, // north
                 4u,  5u,  6u,   6u,  7u,  4u, // west
                 8u,  9u, 10u,  10u, 11u,  8u, // south
                12u, 13u, 14u,  14u, 15u, 12u, // east
                16u, 17u, 18u,  18u, 19u, 16u, // top
                20u, 21u, 22u,  22u, 23u, 20u, // bottom
            };
            node->normal = {
                0.0, 0.0,-1.0,  0.0, 0.0,-1.0,  0.0, 0.0,-1.0,  0.0, 0.0,-1.0, // north
               -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, // west
                0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0, // south
                1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0, // east
                0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0, // top
                0.0,-1.0, 0.0,  0.0,-1.0, 0.0,  0.0,-1.0, 0.0,  0.0,-1.0, 0.0, // bottom
            };
            return node;
        }

        /**
         * @brief SGModel::createQuad
         * @param context Scene graph context ref.
         * @param size {width, height} in units.
         * @return A render scene graph node.
         */
        ISGNode* SGModel::createQuad(SGContext& context, glm::vec2 size)
        {
            auto* node = new SGRenderNode(context);
            size = glm::abs(size/2.f);
            node->grouping = 2; // we have 2d coords

            node->vertex = {
               -size.x,  size.y, // A
               -size.x, -size.y, // B
                size.x, -size.y, // C
                size.x,  size.y, // D
            };
            node->normal = {
                0, 0, 1,
                0, 0, 1,
                0, 0, 1,
                0, 0, 1,
            };
            node->texture = {
                0, 0,
                0, 1,
                1, 1,
                1, 0,
            };
            node->index = {
                0, 1, 2,
                2, 3, 0,
            };
            node->color = {
                0.678f, 0.643f, 0.631f, 1.0f,
                0.678f, 0.643f, 0.631f, 1.0f,
                0.678f, 0.643f, 0.631f, 1.0f,
                0.678f, 0.643f, 0.631f, 1.0f,
            };
            return node;
        }

        SGModel::SGModel()
        {

        }
    }
}
