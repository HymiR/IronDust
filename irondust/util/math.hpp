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


#ifndef MATH_HPP
#define MATH_HPP

#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>

namespace irondust
{
    namespace util
    {
        namespace math
        {
            const glm::f32 PIl = glm::pi<glm::f32>();
            const glm::f32 PI2l = PIl * 2.f;
            const glm::f32 HPIl = PIl / 2.f;

            const glm::f64 PIm = glm::pi<glm::f64>();
            const glm::f64 PI2m = PIm * 2.;
            const glm::f64 HPIm = PIm / 2.;

            glm::f32 ratio(glm::u32 w, glm::u32 h);
            glm::f32 ratio(glm::i32 w, glm::i32 h);
            glm::f32 ratio(glm::f64 w, glm::f64 h);

            glm::f32 bounce_step(glm::f64 t, glm::u32 T=2000, glm::f32 a=1.0, glm::f32 b=0.0);
            glm::f32 rotate_radians(glm::f64 t, glm::u16 speed=30);
        }
    }
}

#endif // MATH_HPP
