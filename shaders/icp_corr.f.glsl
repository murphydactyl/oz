layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;
in struct PerVertex {
	float id;
	float weight;
} neighbor;

void main(void) {
	fragColor.r = neighbor.id;
	fragColor.g = neighbor.weight;
	fragColor.b = 1.0;
	fragColor.a = 1.0;
}
