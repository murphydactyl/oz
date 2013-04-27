uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;
out vec4 fragColor1;
out vec4 fragColor2;
out vec4 fragColor3;

void main(void) {
	int x = int(gl_FragCoord.x);
	int y = int(gl_FragCoord.y);
	
	vec4 t0 = texelFetch(tex0, ivec2(x,				y),	0);
	vec4 t1 = texelFetch(tex1, ivec2(x,				y),	0);
	vec4 t2 = texelFetch(tex2, ivec2(x,				y),	0);
	vec4 t3 = texelFetch(tex3, ivec2(x,				y),	0);
	
	mat3 cov;
	vec3 com_pc;
	vec3 com_pc2;
	
	
	cov[0][0] = t0.r;
	cov[0][1] = t0.g;
	cov[0][2] = t0.b;
	cov[1][0] = t1.r;
	cov[1][1] = t1.g;
	cov[1][2] = t1.b;
	cov[2][0] = t2.r;
	cov[2][1] = t2.g;
	cov[2][2] = t2.b;
	com_pc[0] = t0.a;
	com_pc[1] = t1.a;
	com_pc[2] = t2.a;
	com_pc2[0] = t3.r;
	com_pc2[1] = t3.g;
	com_pc2[2] = t3.b;
	
	fragColor =		t0_0 + t0_1 + t0_2 + t0_3;
	fragColor1 =		t1_0 + t1_1 + t1_2 + t1_3;
	fragColor2 =		t2_0 + t2_1 + t2_2 + t2_3;
	fragColor3 =		t3_0 + t3_1 + t3_2 + t3_3;
}