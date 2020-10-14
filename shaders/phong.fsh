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


#version 120


/**
 * definition of a material structure containing common properties
 */
struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

/**
 * definition of the light properties related to material properties
 */
struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


// bitfield constants for feature enabling
// --------------------------------------------
const int TEX = 0;
const int TEX_ANIM = 1;


// shader parameters
// --------------------------------------------
//illumination related variables
uniform Material u_material;
uniform Light u_light;

// bit set general options
uniform bool u_options[16];

//texture related variables
uniform sampler2D u_tex_object;


// shader stage input
// --------------------------------------------
varying vec4 v_color;

varying vec3 v_normalVec;
varying vec3 v_eyeVec;
varying vec3 v_lightVec;
varying vec2 v_texCoord;



bool use(int option)
{
	return u_options[option];
}


vec4 pointLight(Light light, Material material, vec3 lightVec, vec3 normalVec, vec3 eyeVec)
{
	// calculate texture colors with lighting
    float alpha = 1.0;
	if (use(TEX)) {
		vec4 textureColor = texture2D(u_tex_object, v_texCoord);
        alpha = textureColor.a;
        if(alpha == 0.0) discard;
		material.ambient *= textureColor;
		material.diffuse *= textureColor;
        material.emission.a *= alpha;
	}

    // compute ambient term
	vec4 c_amb = clamp(light.ambient * material.ambient, 0.0, 1.0);

    // compute diffuse term
    float diffuse = max(dot(normalVec, lightVec), 0.0);
	vec4 c_diff = clamp(diffuse * light.diffuse * material.diffuse, 0.0, 1.0);

    // compute specular term
    vec3 reflectVec = reflect(-lightVec, normalVec);
    float spec = pow(max(dot(reflectVec, eyeVec), 0.0), material.shininess);
    vec4 c_spec = clamp(spec * light.specular * material.specular, 0.0, 1.0);
    c_spec.a *= alpha;

    return c_amb + c_diff + c_spec + material.emission;
}


void main(void)
{
    gl_FragColor = pointLight(u_light, u_material, v_lightVec, v_normalVec, v_eyeVec);
}
