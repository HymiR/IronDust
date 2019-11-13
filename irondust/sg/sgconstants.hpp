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


#ifndef SGCONSTANTS_HPP
#define SGCONSTANTS_HPP

#include <string>

#include <glm/fwd.hpp>


namespace irondust
{
    namespace sg
    {
        namespace options
        {
            const glm::u32 TEX {0x1};
            const glm::u32 TEX_ANIM {0x2};
        }

        namespace attrib
        {
            const std::string VERTEX {"a_position"};
            const std::string TEXTURE {"a_texture"};
            const std::string NORMAL {"a_normal"};
            const std::string COLOR {"a_color"};
        }

        namespace uniform
        {
            // options bitset parameter
            const std::string OPTIONS {"u_options"};

            // material parameters
            const std::string MATERIAL_AMBIENT {"u_material.ambient"};
            const std::string MATERIAL_DIFFUSE {"u_material.diffuse"};
            const std::string MATERIAL_SPECULAR {"u_material.specular"};
            const std::string MATERIAL_EMISSION {"u_material.emission"};
            const std::string MATERIAL_SHININESS {"u_material.shininess"};

            // lighting parameters
            const std::string LIGHT_AMBIENT {"u_light.ambient"};
            const std::string LIGHT_DIFFUSE {"u_light.diffuse"};
            const std::string LIGHT_SPECULAR {"u_light.specular"};
            const std::string LIGHT_POS {"u_lightPos"};

            // transformation matrices
            const std::string MAT_NORMAL {"u_normal_mat"};
            const std::string MAT_PROJ {"u_projection_mat"};
            const std::string MAT_MODELVIEW {"u_modelview_mat"};
            const std::string MAT_TEXTURE {"u_texture_mat"};

            // texture specific parameters
            const std::string TEX_OBJECT {"u_tex_object"};
        }
    }
}

#endif // SGCONSTANTS_HPP
