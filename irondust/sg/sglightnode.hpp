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


#ifndef SGLIGHTNODE_HPP
#define SGLIGHTNODE_HPP

#include <irondust/sg/sgnode.hpp>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>


namespace irondust
{
    namespace sg
    {
        class SGLightNode : public SGNode
        {
            typedef SGNode base;

        public:
            glm::vec4 ambient;
            glm::vec4 diffuse;
            glm::vec4 specular;

            SGLightNode(ISGNode* child, glm::vec3 position=glm::vec3(0, 0, 0));
            SGLightNode(glm::vec3 position=glm::vec3(0, 0, 0));

            // ISGNode interface
            virtual void render(SGContext& context) override;

        private:
            glm::vec3 position;
        };
    }
}

#endif // SGLIGHTNODE_HPP
