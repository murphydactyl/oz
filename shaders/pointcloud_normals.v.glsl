in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;

out VertexData {
	vec3 C;
	vec3 N;
} vertex;

void main(void)
{
	vertex.N = v_normal;
	vertex.C = v_color;
  gl_Position = vec4(v_position, 1);
}
