#version 120

// vertex attributes
// --------------------------------------------
attribute vec3 a_position;
attribute vec4 a_color;

// shader parameters
// --------------------------------------------
uniform mat4 u_projection_mat;
uniform mat4 u_modelview_mat;

// output to next shader stage
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
	if(a_color == vec4(0))
		v_color = vec4(1, 1, 1, 1); // simply white.
	else
		v_color = a_color;
}

