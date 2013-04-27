out vec4 fragColor;
uniform sampler2D tex2D_pos;
void main() {
	int ux = int(gl_FragCoord.x);
	int uy = int(gl_FragCoord.y);
	ivec2 origin = ivec2(ux, uy);
	vec3 o = texelFetch(tex2D_pos, origin, 0).xyz;
	vec3 n = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+0, +1)).xyz;
	vec3 ne = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+1, +1)).xyz;
	vec3 e = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+1, +0)).xyz;
	vec3 se = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+1, -1)).xyz;
	vec3 s = texelFetchOffset(tex2D_pos, origin, 0, ivec2(+0, -1)).xyz;
	vec3 sw = texelFetchOffset(tex2D_pos, origin, 0, ivec2(-1, -1)).xyz;
	vec3 w = texelFetchOffset(tex2D_pos, origin, 0, ivec2(-1, +0)).xyz;
	vec3 nw = texelFetchOffset(tex2D_pos, origin, 0, ivec2(-1, +1)).xyz;
	vec3 on = n - o;
	vec3 one = ne - o;
	vec3 oe = e - o;
	vec3 ose = se - o;
	vec3 os = s - o;
	vec3 osw = sw - o;
	vec3 ow = w - o;
	vec3 onw = nw - o;
	float on_l = length(on);
	float one_l = length(one);
	float oe_l = length(oe);
	float ose_l = length(ose);
	float os_l = length(os);
	float osw_l = length(osw);
	float ow_l = length(ow);
	float onw_l = length(onw);
	on = on / on_l;
	one = one / one_l;
	oe = oe / oe_l;
	ose = ose / ose_l;
	os = os / os_l;
	osw = osw / osw_l;
	ow = ow / ow_l;
	onw = onw / onw_l;
	vec3 on_one = cross(on, one);
	vec3 one_oe = cross(one, oe);
	vec3 oe_ose = cross(oe, ose);
	vec3 ose_os = cross(ose, os);
	vec3 os_osw = cross(os, osw);
	vec3 osw_ow = cross(osw, ow);
	vec3 ow_onw = cross(ow, onw);
	vec3 onw_on = cross(onw, on);

	float w_on_one = 0;
	float w_one_oe = 0;
	float w_oe_ose = 0;
	float w_ose_os = 0;
	float w_os_osw = 0;
	float w_osw_ow = 0;
	float w_ow_onw = 0;
	float w_onw_on = 0;
	
	if (on_l < LMAX && one_l < LMAX) {
		w_on_one = acos(dot(on, one));
	}
	
	if (one_l < LMAX && oe_l < LMAX) {
		w_one_oe = acos(dot(one, oe));
	}
	
	if (oe_l < LMAX && ose_l < LMAX) {
		w_oe_ose = acos(dot(oe, ose));
	}
	
	if (ose_l < LMAX && os_l < LMAX) {
		w_ose_os = acos(dot(ose, os));
	}
	
	if (os_l < LMAX && osw_l < LMAX) {
		w_os_osw = acos(dot(os, osw));
	}

	if (osw_l < LMAX && ow_l < LMAX) {
		w_osw_ow = acos(dot(osw, ow));
	}
	
	if (ow_l < LMAX && onw_l < LMAX) {
		w_ow_onw = acos(dot(ow, onw));
	}
	
	if (onw_l < LMAX && on_l < LMAX) {
		w_onw_on = acos(dot(onw, on));
	}

	float w_total = 	w_on_one + w_one_oe + w_oe_ose + w_ose_os + w_os_osw + w_osw_ow + w_ow_onw + w_onw_on;
		
	vec3 dir = on_one * w_on_one;
	dir += one_oe * w_one_oe;
	dir += oe_ose * w_oe_ose;
	dir += ose_os * w_ose_os;
	dir += os_osw * w_os_osw;
	dir += osw_ow * w_osw_ow;
	dir += ow_onw * w_ow_onw;
	dir += onw_on * w_onw_on;

	dir = normalize(dir);
	fragColor = vec4(dir,1);
}