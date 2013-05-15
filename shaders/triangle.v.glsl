uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 i;
in vec3 v_position;
in vec4 v_color;
out vec4 C;

void main(void) {
  gl_Position = p * v * m * vec4(v_position, 1.0);
  C = v_color;
}
