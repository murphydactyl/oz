#define W 640
#define W2 320.0
#define H 480
#define H2 240.0

in uint uDepth;
out float fDepth;

void main(void)
{
	if (uDepth > uint(0)) {
		int x = (gl_VertexID) % W;
		int y = (gl_VertexID) / W;
		float xn = float(x + 0.5) / W2 - 1;
		float yn = float(y + 0.5) / H2 - 1;
		fDepth = float(uDepth);
		gl_Position = vec4(xn, yn, 0, 1.0);
	} else {
		gl_Position = vec4(0, 0, 0, 1);
	}
	
	gl_PointSize = 1.0;
}