#version 120

// from vertex shader stage
// --------------------------------------------
varying vec4 v_color;


void main()
{
	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	gl_FragColor = v_color;
}
