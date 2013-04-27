uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform int tex_width;
uniform int tex_height;
layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;
out vec4 fragColor1;
out vec4 fragColor2;

void main(void) {
	int x = 2 * int(gl_FragCoord.x);
	int y = 2 * int(gl_FragCoord.y);
	vec4 t0_1 = texelFetch(tex0, ivec2(x,			y), 0);
	vec4 t0_2 = texelFetch(tex0, ivec2(x + 1,		y), 0);
	vec4 t0_3 = texelFetch(tex0, ivec2(x,			y + 1), 0);
	vec4 t0_4 = texelFetch(tex0, ivec2(x + 1,		y + 1), 0);
	vec4 t1_1 = texelFetch(tex1, ivec2(x,			y), 0);
	vec4 t1_2 = texelFetch(tex1, ivec2(x + 1,		y), 0);
	vec4 t1_3 = texelFetch(tex1, ivec2(x,			y + 1), 0);
	vec4 t1_4 = texelFetch(tex1, ivec2(x + 1,		y + 1), 0);
	vec4 t2_1 = texelFetch(tex2, ivec2(x,			y), 0);
	vec4 t2_2 = texelFetch(tex2, ivec2(x + 1,		y), 0);
	vec4 t2_3 = texelFetch(tex2, ivec2(x,			y + 1), 0);
	vec4 t2_4 = texelFetch(tex2, ivec2(x + 1,		y + 1), 0);
	fragColor = t0_1 + t0_2 + t0_3 + t0_4;
	fragColor1 = t1_1 + t1_2 + t1_3 + t1_4;
	fragColor2 = t2_1 + t2_2 + t2_3 + t2_4;
}