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


#ifndef SGMODEL_HPP
#define SGMODEL_HPP

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace irondust
{
    namespace sg
    {
        class ISGNode;
        class SGContext;


        class SGModel
        {
        public:
            static ISGNode* createSphere(SGContext& context, glm::f32 radius=2.f, glm::uvec2 grid={30, 30});
            static ISGNode* createPyramid(SGContext& context, glm::f32 s=1.0f, glm::f32 h=0.75f);
            static ISGNode* createCube(SGContext& context, glm::vec3 size={1.f, 1.f, 1.f});
            static ISGNode* createQuad(SGContext& context, glm::vec2 size={2.f, 2.f});

        protected:
            SGModel();
        };
    }
}
#endif // SGMODEL_HPP
