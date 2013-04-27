out vec4 fragColor;
layout(pixel_center_integer) in vec4 gl_FragCoord;
in vec4 C;
void main(void) {
	fragColor = C;
}
