uniform usampler2D tex;
uniform float max_value;
uniform float min_value;
in vec2 f_texcoord;
out vec4 fragColor;
layout(pixel_center_integer) in vec4 gl_FragCoord;

void main(void) {
	uint t = texture(tex, f_texcoord).r;
	float r = max_value - min_value;
	float s = (t - min_value) / r;
	fragColor = vec4(s, s, s, 1.0);
}