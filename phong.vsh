#version 120
// Phong Vertex Shader


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
uniform mat4 u_modelview_mat;
uniform mat3 u_normal_mat;
uniform mat4 u_projection_mat;
uniform mat4 u_invView;

uniform vec3 u_lightPos;

//uniform vec2 u_texoffset;
uniform mat3 u_texMatrix;

// bit set general options
uniform bool u_options[64];


// output to next shader stage
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


	// apply texture transformation if such a matrix is provided (i.e. it is not a null matrix)
	if(use(TEX) && use(TEX_ANIM)) {
		vec3 txc = vec3(a_texture, 1) * u_texMatrix; // WTF!? are vectors treated as line vectors rather than column vectors?!
		v_texCoord = txc.xy;
	} else {
		v_texCoord = a_texture;
	}

	gl_Position = u_projection_mat * eyePosition;
}
