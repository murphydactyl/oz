in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;
uniform mat4 inv_v;
out vec3 C;
out vec3 N;

void main(void)
{
	float size = 0.25;
  vec4 pos = m * vec4(v_position, 1);
	float L = length(v_normal);
	vec3 N = normalize(inv_trans_3x3_m * v_normal);
	C = v_color;
  float view_dist = length(pos - inv_v[3]);
  gl_PointSize = size * 2000 / view_dist;
  gl_Position = p * v * pos;
}
