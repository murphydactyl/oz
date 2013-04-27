out vec4 fragColor;
layout(pixel_center_integer) in vec4 gl_FragCoord;

void main(void) {
	float x = gl_FragCoord.x - 320;
	float y = gl_FragCoord.y - 240;
	if (x * x + y * y < 100 * 100) {
		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
	} else {
		fragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	gl_FragDepth = 0.5;
}
