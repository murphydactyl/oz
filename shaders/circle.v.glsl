uniform mat4 m;
in vec3 v_position;
void main(void) {
  gl_Position = m * vec4(v_position, 1.0);
}