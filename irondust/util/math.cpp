/**
 ** This file is part of the cg project.
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


#include <irondust/util/math.hpp>


namespace irondust
{
    namespace util
    {
        namespace math
        {
            glm::f32 ratio(glm::u32 w, glm::u32 h)
            {
                return static_cast<glm::f32>(static_cast<glm::f64>(w) / h);
            }

            glm::f32 ratio(glm::i32 w, glm::i32 h)
            {
                return glm::abs(static_cast<glm::f32>(static_cast<glm::f64>(w) / h));
            }

            glm::f32 ratio(glm::f64 w, glm::f64 h)
            {
                return glm::abs(static_cast<glm::f32>(w / h));
            }


            glm::f32 bounce_step(glm::f64 t, glm::u32 T, glm::f32 a, glm::f32 b)
            {
                glm::f64 w = PI2m / T;
                return glm::abs(static_cast<glm::f32>(glm::sin(w*t))*a) + b;
            }

            glm::f32 rotate_radians(glm::f64 t, glm::u16 speed)
            {
                glm::f64 deg = fmod(t / speed, 360);
                return static_cast<glm::f32>(glm::radians(deg));
            }
        }
    }
}
