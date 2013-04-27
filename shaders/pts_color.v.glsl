uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
in vec4 v_position;
out vec4 C;

void main(void)
{
  gl_Position = p * v * m * v_position;
	gl_PointSize = 1.0;
	C = vec4(1.0, 1.0, 0.0, 1.0);
}
