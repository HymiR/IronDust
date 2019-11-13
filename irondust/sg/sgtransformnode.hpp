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


#ifndef SGTRANSFORMNODE_HPP
#define SGTRANSFORMNODE_HPP

#include <irondust/sg/sgnode.hpp>

#include <glm/mat4x4.hpp>

#include <initializer_list>


namespace irondust
{
    namespace sg
    {
        class SGTransformNode : public SGNode
        {
            typedef SGNode base;

        public:
            SGTransformNode(const glm::mat4& matrix, const std::initializer_list<ISGNode*>& children={});

            // ISGNode interface
            virtual void render(SGContext& context) override;

        protected:
            glm::mat4 matrix;
        };
    }
}

#endif // SGTRANSFORMNODE_HPP
