uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
in vec3 v_position;
in vec4 v_color;
out vec4 C;
void main(void) {

	C = v_color;
	gl_Position = p * v * m * vec4(v_position, 1.0);
}