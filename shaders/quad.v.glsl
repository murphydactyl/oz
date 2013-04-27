in vec3 v_position;
out vec2 f_texcoord;
void main() {
	f_texcoord = (v_position.xy + 1) / 2.0;
	gl_Position = vec4(v_position, 1.0);
}