/**
 ** This file is part of the irondust project.
 ** Copyright 2020 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
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

/**
 * Simple environment mapping shader.
 * Vertex shader.
 */


#version 120

precision highp float;

// attributes: per vertex inputs in this case the 2d position and its color
attribute vec3 a_position;
attribute vec3 a_normal;

uniform mat4 u_modelview_mat;
uniform mat4 u_projection_mat;
uniform mat3 u_normal_mat;
uniform mat3 u_invview_mat; // get from eye to world space

// output variables requried in fragment shader
varying vec3 v_normalVec;
varying vec3 v_cameraRayVec;

void main()
{
    // calculate vertex position in eye space (!vertex position in eye space = camera ray in eye space!)
    vec4 eyePosition = u_modelview_mat * vec4(a_position, 1);

    // transform camera ray direction to world space
    v_cameraRayVec = normalize(u_invview_mat * eyePosition.xyz);

    // calculate normal vector in world space
    v_normalVec = normalize(u_invview_mat * u_normal_mat * a_normal);

    gl_Position = u_projection_mat * eyePosition;
}
