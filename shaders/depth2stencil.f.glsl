#define DEPTHMAX 900
out vec4 fragColor;
uniform sampler2D tex2D_pos;
void main() {
	int ux = int(gl_FragCoord.x);
	int uy = int(gl_FragCoord.y);
	ivec2 origin = ivec2(ux, uy);
	vec3 o = texelFetch(tex2D_pos, origin, 0).xyz;
	if (-o.z < DEPTHMAX) {
		fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	} else {
		fragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
}