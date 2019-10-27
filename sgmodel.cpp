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


#include <geometry.hpp>

#include <sgmodel.hpp>
#include <sgrendernode.hpp>
#include <sgcontext.hpp>

//#include <glm/gtc/constants.hpp>

namespace cg
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
            glm::f32 theta = static_cast<glm::f32>(lat) * PIl / grid.x;
            glm::f32 sinTheta = glm::sin(theta);
            glm::f32 cosTheta = glm::cos(theta);

            for(glm::u16 lon=0; lon<= grid.y; lon++) {
                glm::f32 phi = static_cast<glm::f32>(lon) * PI2l / grid.y;
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

    /**
     * @brief SGModel::createCube
     * @param context Scene graph context ref.
     * @param size {width, height, depth} in units.
     * @return A render scene graph node.
     */
    ISGNode* SGModel::createCube(SGContext& context, glm::vec3 size)
    {
        size = glm::abs(size/2.f);
        auto* node = new SGRenderNode(context);
        node->vertex = {
            -size.x, -size.y, -size.z,
             size.x, -size.y, -size.z,
             size.x,  size.y, -size.z,
            -size.x,  size.y, -size.z,
            -size.x, -size.y,  size.z,
             size.x, -size.y,  size.z,
             size.x,  size.y,  size.z,
            -size.x,  size.y,  size.z,
            -size.x, -size.y, -size.z,
            -size.x,  size.y, -size.z,
            -size.x,  size.y,  size.z,
            -size.x, -size.y,  size.z,
             size.x, -size.y, -size.z,
             size.x,  size.y, -size.z,
             size.x,  size.y,  size.z,
             size.x, -size.y,  size.z,
            -size.x, -size.y, -size.z,
            -size.x, -size.y,  size.z,
             size.x, -size.y,  size.z,
             size.x, -size.y, -size.z,
            -size.x,  size.y, -size.z,
            -size.x,  size.y,  size.z,
             size.x,  size.y,  size.z,
             size.x,  size.y, -size.z,
        };
        node->color = {
            0.583f, 0.771f, 0.014f, 0.6f,
            0.609f, 0.115f, 0.436f, 0.6f,
            0.327f, 0.483f, 0.844f, 0.6f,
            0.822f, 0.569f, 0.201f, 0.6f,
            0.435f, 0.602f, 0.223f, 0.6f,
            0.310f, 0.747f, 0.185f, 0.6f,
            0.597f, 0.770f, 0.761f, 0.6f,
            0.559f, 0.436f, 0.730f, 0.6f,
            0.359f, 0.583f, 0.152f, 0.6f,
            0.483f, 0.596f, 0.789f, 0.6f,
            0.559f, 0.861f, 0.639f, 0.6f,
            0.195f, 0.548f, 0.859f, 0.6f,
            0.014f, 0.184f, 0.576f, 0.6f,
            0.771f, 0.328f, 0.970f, 0.6f,
            0.406f, 0.615f, 0.116f, 0.6f,
            0.676f, 0.977f, 0.133f, 0.6f,
            0.971f, 0.572f, 0.833f, 0.6f,
            0.140f, 0.616f, 0.489f, 0.6f,
            0.997f, 0.513f, 0.064f, 0.6f,
            0.945f, 0.719f, 0.592f, 0.6f,
            0.543f, 0.021f, 0.978f, 0.6f,
            0.279f, 0.317f, 0.505f, 0.6f,
            0.167f, 0.620f, 0.077f, 0.6f,
            0.347f, 0.857f, 0.137f, 0.6f,
            0.055f, 0.953f, 0.042f, 0.6f,
            0.714f, 0.505f, 0.345f, 0.6f,
            0.783f, 0.290f, 0.734f, 0.6f,
            0.722f, 0.645f, 0.174f, 0.6f,
            0.302f, 0.455f, 0.848f, 0.6f,
            0.225f, 0.587f, 0.040f, 0.6f,
            0.517f, 0.713f, 0.338f, 0.6f,
            0.053f, 0.959f, 0.120f, 0.6f,
            0.393f, 0.621f, 0.362f, 0.6f,
            0.673f, 0.211f, 0.457f, 0.6f,
            0.820f, 0.883f, 0.371f, 0.6f,
            0.982f, 0.099f, 0.879f, 0.6f,
        };
        node->index = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            8, 9, 10, 8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23
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
            -size.x,  size.y,
             size.x,  size.y,
             size.x, -size.y,
            -size.x, -size.y,
        };
        node->normal = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
        node->texture = {0, 0 /**/, 1, 0 /**/, 1, 1 /**/, 0, 1};
        node->index = {0, 1, 2, 2, 3, 0};
        node->color = {
            0.5f, 0.5f, 0.3f, 1.0f,
            0.3f, 0.3f, 0.3f, 1.0f,
            0.9f, 0.9f, 0.8f, 1.0f,
            0.9f, 0.9f, 0.8f, 1.0f,
            0.3f, 0.3f, 0.3f, 1.0f,
            0.5f, 0.6f, 0.5f, 1.0f,
        };
        return node;
    }

    SGModel::SGModel()
    {

    }
}
