// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 13.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


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
