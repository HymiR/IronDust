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


#ifndef SGCONTEXT_HPP
#define SGCONTEXT_HPP


#include <glm/glm.hpp>

#include <irondust/gl/GLSLProgram.hpp>


namespace irondust
{
    namespace sg
    {
        class SGScene;

        class SGContext
        {
        public:
            SGContext(SGScene& scene);
            virtual ~SGContext();

            gl::GLSLProgram* program;
            SGScene& scene;

            glm::mat4 scene_matrix;
            glm::mat4 view_matrix;
            glm::mat4 projection_matrix;
        };
    }
}


#endif // SGCONTEXT_HPP
