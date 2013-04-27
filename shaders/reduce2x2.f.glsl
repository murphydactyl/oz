uniform sampler2D tex;
uniform int tex_width;
uniform int tex_height;
layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;

void main(void) {
	int x = 2 * int(gl_FragCoord.x);
	int y = 2 * int(gl_FragCoord.y);
	vec4 t1 = texelFetch(tex, ivec2(x,			y), 0);
	vec4 t2 = texelFetch(tex, ivec2(x + 1,		y), 0);
	vec4 t3 = texelFetch(tex, ivec2(x,			y + 1), 0);
	vec4 t4 = texelFetch(tex, ivec2(x + 1,		y + 1), 0);
	fragColor = vec4(t1.r + t2.r + t3.r + t4.r, 0, 0, 1);
}