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


#ifndef SGRENDERNODE_HPP
#define SGRENDERNODE_HPP


#include <irondust/sg/isgresourcenode.hpp>

#include <glm/fwd.hpp>

#include <vector>


namespace irondust
{
    namespace sg
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
}

#endif // SGRENDERNODE_HPP
