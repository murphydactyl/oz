uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 i;
in vec3 v_position;
in vec2 v_texcoord;

out vec2 f_texcoord;

void main(void) {
  gl_Position = p * v * m * vec4(v_position, 1.0);
  f_texcoord = v_texcoord;
}
