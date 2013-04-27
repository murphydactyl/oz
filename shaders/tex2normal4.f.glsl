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
	float on_l = length(on);
	float oe_l = length(oe);
	float os_l = length(os);
	float ow_l = length(ow);
	on = on / on_l;
	oe = oe / oe_l;
	os = os / os_l;
	ow = ow / ow_l;
	vec3 on_oe = cross(on, oe);
	vec3 oe_os = cross(oe, os);
	vec3 os_ow = cross(os, ow);
	vec3 ow_on = cross(ow, on);

	float w_on_oe = 0;
	float w_oe_os = 0;
	float w_os_ow = 0;
	float w_ow_on = 0;
	
	if (on_l < LMAX && oe_l < LMAX) {
		w_on_oe = acos(dot(on, oe));
	}

	if (oe_l < LMAX && os_l < LMAX) {
		w_oe_os = acos(dot(oe, os));
	}
	
	if (os_l < LMAX && ow_l < LMAX) {
		w_os_ow = acos(dot(os, ow));
	}
	
	if (ow_l < LMAX && on_l < LMAX) {
		w_ow_on = acos(dot(ow, on));
	}

	float w_total = 	w_on_oe + w_oe_os + w_os_ow + w_ow_on;
		
	vec3 dir = on_oe * w_on_oe;
	dir += oe_os * w_oe_os;
	dir += os_ow * w_os_ow;
	dir += ow_on * w_ow_on;

	dir = normalize(dir);
	fragColor = vec4(dir,1);
}