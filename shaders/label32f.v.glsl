uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 i;

in vec3 v_position;
in vec3 v_color;

out vec3 f_color;

void main(void) {
  vec3 dummy_for_i = i * v_position;
  gl_Position = p * v * m * vec4(v_position, 1.0);
  f_color = v_color;
}