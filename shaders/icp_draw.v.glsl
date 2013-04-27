uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
in vec3 v_position;
in vec3 v_normal;
uniform sampler2D u_positions;
uniform sampler2D u_ids;

out VertexData {
	vec4 N;
} vertex;

void main(void) {
	vec3 dummy = v_normal;
	vec4 id = texelFetch(u_ids, ivec2(gl_VertexID, 0), 0);
	int my_closest = int(id.r);
	vec4 my_closest_pos;
	if (id.r >= 0) {
		my_closest_pos = texelFetch(u_positions, ivec2(my_closest, 0), 0);
		vertex.N = vec4(my_closest_pos.xyz,1.0);
		gl_Position = m * vec4(v_position, 1.0);
	} else {
		gl_Position = vec4(0,0,0,1.0);
		vertex.N = vec4(0,0,0,1.0);
	}
}