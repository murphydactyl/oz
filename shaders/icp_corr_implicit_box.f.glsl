uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec4 model;
uniform mat3 inv_trans_3x3_m;
uniform float D_THRESH;
uniform sampler2D o_position;
uniform sampler2D o_normal;
struct PerFragment {
	float id;
	float weight;
} neighbor;

out vec4 fragColor;
out vec4 fragColor1;
out vec4 fragColor2;
out vec4 fragColor3;
out vec4 fragColor4;

void main(void) {
	ivec2 fCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	vec3 my_position = (texelFetch(o_position, fCoord, 0)).xyz;
	vec3 my_normal = normalize(texelFetch(o_normal, fCoord, 0).xyz);
	mat3 B = inverse(mat3(m));
	vec3 O = (m[3]).xyz;
	vec3 S = model.xyz;
	vec3 U = B * (my_position - O);
	vec3 best_mag = min(S, abs(U));
	vec3 best_position = best_mag * sign(U);
	vec3 best_dir = best_position - U;
	float bestd = dot(best_dir, best_dir);
	best_position = (m * vec4(best_position, 1)).xyz;
	if (bestd < D_THRESH * D_THRESH) {
		neighbor.id = 0;
		neighbor.weight = 1 / sqrt(bestd + 1);
		mat3 cov = neighbor.weight * outerProduct(my_position, best_position);
		vec3 my_avg_trans = neighbor.weight * my_position;
		fragColor = vec4(cov[0], my_avg_trans.x);
		fragColor1 = vec4(cov[1], my_avg_trans.y);
		fragColor2 = vec4(cov[2], my_avg_trans.z);
		fragColor3 = neighbor.weight * vec4(best_position, 1);

	} else {
		neighbor.id = -1;
		neighbor.weight = 0;
	}

	fragColor4 = vec4(neighbor.id, best_position);

}