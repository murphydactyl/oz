#define LMAX 10000
out vec4 fragColor;
uniform sampler2D tex2D_pos;
void main() {
	int ux = int(gl_FragCoord.x);
	int uy = int(gl_FragCoord.y);
	ivec2 origin = ivec2(ux, uy);
	vec3 o = texelFetch(tex2D_pos, origin, 0).xyz;
	vec3 n = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+0, +1)).xyz;
	vec3 e = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+1, +0)).xyz;
	vec3 s = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+0, -1)).xyz;
	vec3 w = texelFetchOffset(tex2D_pos, origin, 0, ivec2(-1, +0)).xyz;
	vec3 on = n - o;
	vec3 oe = e - o;
	vec3 os = s - o;
	vec3 ow = w - o;
	float on_l = dot(on,on);
	float oe_l = dot(oe,oe);
	float os_l = dot(os,os);
	float ow_l = dot(ow,ow);
	vec3 on_oe = cross(on, oe);
	vec3 oe_os = cross(oe, os);
	vec3 os_ow = cross(os, ow);
	vec3 ow_on = cross(ow, on);
	
	vec3 dir = vec3(0,0,0);
	
	if (on_l < LMAX && oe_l < LMAX) {
		dir += on_oe;
	}

	if (oe_l < LMAX && os_l < LMAX) {
		dir += oe_os;
	}
	
	if (os_l < LMAX && ow_l < LMAX) {
		dir += os_ow;
	}
	
	if (ow_l < LMAX && on_l < LMAX) {
		dir += ow_on;
	}

	dir = normalize(dir);
	fragColor = vec4(dir,1);
}