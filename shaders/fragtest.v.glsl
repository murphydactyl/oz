in vec3 v_position;
out vec4 C;
void main(void) {
	vec3 r = v_position;
	int idx = gl_VertexID;
	int ix = idx % 1024;
	int iy = idx / 1024;
	if (ix % 2 == 0)
		C = vec4(1.0, 1.0, 0.0, 1.0);
	else
		C = vec4(1.0, 1.0, 1.0, 1.0);
	
	float x = ix / (512.0) - 1;
	float y = iy / (384.0) - 1;

	gl_Position = vec4(x, y, 0.99, 1.0);
	gl_PointSize = 1.0;
}