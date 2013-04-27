#define fx2z 1.1114666461944582
#define fy2z 0.8335999846458435

layout(pixel_center_integer) in vec4 gl_FragCoord;
uniform usampler2D tex2D_pos;
uniform int image_width;
uniform int image_height;
out vec4 fragColor;
in vec2 f_texcoord;

void main(void) {
	float z = texture(tex2D_pos, f_texcoord).r;
	float x = (gl_FragCoord.x / image_width - 0.5) * z * fx2z;
	float y = (0.5 - gl_FragCoord.y / image_height) * z * fy2z;
	if (z == 0) {
		fragColor = vec4(x, y, -300, 1.0);
	} else {
		fragColor = vec4(x, y, -z, 1.0);
	}
}