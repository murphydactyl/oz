in vec4 v_position;
in vec4 v_normal;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out VertexData {
	vec3 C;
	vec3 N;
} vertex;

void main(void)
{
	vertex.N = vec3(normalize(v_normal));
	vertex.C = vec3(normalize(vertex.N));
  gl_Position = v_position;
}
