uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform int image_width;
uniform sampler2D positions;
out vec4 C;

void main(void)
{
	int s = gl_InstanceID % image_width;
	int t = gl_InstanceID / image_width;
	vec4 pos = texelFetch(positions, ivec2(s, t), 0);
	if (pos.z == 0) {
		gl_Position = vec4(-2, 0, 0, 1);
	} else {
		gl_Position = p * v * m * pos;
		gl_PointSize = 1.0;
		C = vec4(1.0, 0.0, 0.0, 1.0);
	}
}