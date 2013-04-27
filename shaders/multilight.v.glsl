in vec3 v_position;
in vec3 v_normal;
in vec4 v_color;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;
uniform int showNormals;
out vec4 P;
out vec3 N;
out vec4 C;

struct material
{
	vec4 ambient;
  vec4 diffuse;
	vec4 specular;
};

void main(void)
{
	P = m * vec4(v_position, 1);
	N = normalize(inv_trans_3x3_m * v_normal);
	if (showNormals == 0)
		C = v_color;
	else
		C = vec4(N,1.0);
  gl_Position = p * v * P;
}