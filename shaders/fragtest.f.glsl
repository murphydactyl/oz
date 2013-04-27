in vec4 C;
out vec4 fragColor;
layout(pixel_center_integer) in vec4 gl_FragCoord;
void main(void) {
	fragColor = C;
}
