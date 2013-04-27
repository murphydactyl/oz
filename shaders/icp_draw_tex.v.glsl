uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform int width;
uniform sampler2D i_positions;
uniform sampler2D u_ids;

out VertexData {
	vec4 N;
} vertex;

void main(void) {
	ivec2 idx = ivec2(gl_InstanceID % width, gl_InstanceID / width);
	if (gl_InstanceID % 3 == 0) {
		gl_Position = texelFetch(i_positions, idx, 0);
		vec4 id = texelFetch(u_ids, idx, 0);
		if (id.r >= 0) {
			vertex.N = vec4(id.y, id.z, id.w, 1.0);
		}
	}
}