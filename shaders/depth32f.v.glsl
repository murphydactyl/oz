uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
in vec3 v_normal;
in vec3 v_color;
in vec3 v_position;
out vec4 view_position;

void main(void) {
	vec3 dummy = v_normal + v_normal + v_color;
	vec3 dummy2 = dummy + v_position;
  view_position = v * m * vec4(v_position, 1.0);
  gl_Position = p * view_position;
	gl_PointSize = 1.0;
}