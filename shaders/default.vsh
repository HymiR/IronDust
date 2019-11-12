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


// vertex attributes
// --------------------------------------------
attribute vec3 a_position;
attribute vec4 a_color;

// shader parameters
// --------------------------------------------
uniform mat4 u_projection_mat;
uniform mat4 u_modelview_mat;

// shader stage output
// --------------------------------------------
varying vec4 v_color;


void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = u_projection_mat
		* u_modelview_mat
		* vec4(a_position, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	if(length(a_color) == 0)
		v_color = vec4(1, .2, .2, 0.5); // transparent red.
	else
		v_color = a_color;
}
