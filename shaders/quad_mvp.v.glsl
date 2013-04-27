uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
in vec3 v_position;
out vec2 f_texcoord;
void main() {
	f_texcoord = (v_position.xy + 1) / 2.0;
	vec4 pos = p * v * m * vec4(v_position.xy, 0, 1);
	gl_Position = pos;
}