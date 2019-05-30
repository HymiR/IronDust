#version 120

/**
 * a phong shader implementation with texture support
 */


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
uniform bool u_options[64];

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


vec4 calculateSimplePointLight(Light light, Material material, vec3 lightVec, vec3 normalVec, vec3 eyeVec)
{
	// You can find all built-in functions (min, max, clamp, reflect, normalize, etc.)
	// and variables (gl_FragCoord, gl_Position) in the OpenGL Shading Language Specification:
	// https://www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.4.60.html#built-in-functions
	lightVec = normalize(lightVec);
	normalVec = normalize(normalVec);
	eyeVec = normalize(eyeVec);

	//compute diffuse term
	float diffuse = max(dot(normalVec, lightVec), 0.0);

	//compute specular term
	vec3 reflectVec = reflect(-lightVec, normalVec);
	float spec = pow(max(dot(reflectVec, eyeVec), 0.0), material.shininess);

	// calculate texture colors with lighting
	if (use(TEX)) {
		vec4 textureColor = texture2D(u_tex_object, v_texCoord);
		material.ambient *= textureColor;
		material.diffuse *= textureColor;
	}

	vec4 c_amb = clamp(light.ambient * material.ambient, 0.0, 1.0);
	vec4 c_diff = clamp(diffuse * light.diffuse * material.diffuse, 0.0, 1.0);
	vec4 c_spec = clamp(spec * light.specular * material.specular, 0.0, 1.0);
	vec4 c_em = material.emission;

	return c_amb + c_diff + c_spec + c_em;
}


void main(void)
{
	gl_FragColor = calculateSimplePointLight(u_light, u_material, v_lightVec, v_normalVec, v_eyeVec);
	//gl_FragColor = v_color;
}
