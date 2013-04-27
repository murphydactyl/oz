uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;
uniform sampler2D positions;
uniform sampler2D normals;
uniform int image_width;

out VertexData {
	vec3 C;
	vec3 N;
} vertex;

void main(void)
{	
	ivec2 idx = ivec2(gl_InstanceID % image_width, gl_InstanceID / image_width);
	vec4 pos = vec4(texelFetch(positions, idx, 0).xyz, 1);
	vec3 nor = texelFetch(normals, idx, 0).xyz;
	if (pos.z == 0) {
		gl_Position = vec4(-2, 0, 0, 1);
	} else {
		gl_Position = pos;
		vertex.N = nor;
	}
}
