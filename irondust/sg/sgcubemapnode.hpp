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


#ifndef SGCUBEMAPNODE_HPP
#define SGCUBEMAPNODE_HPP

#include "irondust/sg/isgresourcenode.hpp"

#include <glm/fwd.hpp>

#include <array>
#include <string>
#include <memory>


namespace irondust
{
    namespace gl
    {
        class Image;
    }

    namespace sg
    {
        class SGCubemapNode : public ISGResourceNode
        {
            typedef ISGResourceNode base;

        public:
            //SGCubemapNode(SGContext& context, const std::array<gl::Image*, 6>& faces, bool reflect=false);
            SGCubemapNode(SGContext& context, const std::array<std::string, 6>& faces, bool reflect=false);
            SGCubemapNode(SGContext& context, const SGCubemapNode* other);

            virtual ~SGCubemapNode() override;

            // ISGResource interface
            virtual bool init(SGContext& context) override;

            // ISGElement interface
            virtual void render(SGContext& context) override;

        protected:
            virtual void bind();
            virtual void unbind();

        private:
            std::array<std::shared_ptr<gl::Image>, 6> faces;
            glm::uint id;
            int unit;
            bool reflect;
        };
    }
}
#endif // SGCUBEMAPNODE_HPP
