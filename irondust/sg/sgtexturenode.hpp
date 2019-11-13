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
