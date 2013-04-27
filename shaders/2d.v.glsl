in vec3 v_position;
in vec4 v_color;
out vec4 f_color;
uniform mat4 m;

void main(void) {
  gl_Position = m * vec4(v_position, 1.0);
  f_color = v_color;
}