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


// constants
// --------------------------------------------
const float PI2 = 6.28318530718;

// bitfield constants for feature enabling
const int TEX = 0;
const int TEX_ANIM = 1;


// vertex attributes
// --------------------------------------------
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec2 a_texture;


// shader parameters
// --------------------------------------------
uniform mat4 u_projection_mat;
uniform mat4 u_modelview_mat;
//uniform mat4 u_invview_mat;
uniform mat3 u_normal_mat;
uniform mat3 u_texture_mat;

uniform vec3 u_lightPos;


// bit set general options
uniform bool u_options[16];


// shader stage output
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


void main()
{
	// pass static color (only used when no material, no texture)
	v_color = a_color;

	vec4 eyePosition = u_modelview_mat * vec4(a_position, 1);
	v_normalVec = u_normal_mat * a_normal;
	v_eyeVec = -eyePosition.xyz;
	v_lightVec = u_lightPos - eyePosition.xyz;


	// apply texture transformation if specifyed by options:
	if(use(TEX) && use(TEX_ANIM)) {
		vec3 txc = vec3(a_texture, 1) * u_texture_mat; // WTF!? are vectors treated as line vectors rather than column vectors?!
		v_texCoord = txc.xy;
	} else if(use(TEX)) {
		v_texCoord = a_texture;
	}

	gl_Position = u_projection_mat * eyePosition;
}
