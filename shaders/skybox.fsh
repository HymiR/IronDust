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
 * Fragment shader.
 */


#version 120

// need to specify how "precise" float should be
precision highp float;

// bitfield constants for feature enabling
const int TEX = 0;
const int TEX_ANIM = 1;
const int REFLECT = 2;

varying vec3 v_normalVec;
varying vec3 v_cameraRayVec;

// bit set general options
uniform bool u_options[16];

uniform samplerCube u_texCube;


bool use(int option)
{
    return u_options[option];
}

void main()
{
    vec3 texCoords;

    // TODO check why this has to be negated! see Image.cpp flip!
    // compute reflected camera ray (assign to texCoords)
    if (use(REFLECT)) texCoords = reflect(-v_cameraRayVec, v_normalVec);
    else texCoords = -v_cameraRayVec;

    // texture lookup in cube map using the textureCube function
    gl_FragColor = textureCube(u_texCube, texCoords);
}
