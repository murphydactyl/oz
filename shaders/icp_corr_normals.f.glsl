uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;
uniform float D_THRESH;
uniform int compSize;
uniform sampler2D o_position;
uniform sampler2D o_normal;
uniform sampler2D u_position;
uniform sampler2D u_normal;
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
	float bestd = D_THRESH * D_THRESH;
	int otheri = -1;
	vec3 best_position;
	float best_similarity = -1;
	for (int i = 0; i < compSize; i++) {
		vec3 t_position = (m * vec4(texelFetch(u_position, ivec2(i, 0), 0))).xyz;
		vec3 t_normal = inv_trans_3x3_m * texelFetch(u_normal, ivec2(i, 0), 0).xyz;
		vec3 diff = t_position - my_position;
		float d = dot(diff,diff);
		float similarity = dot(t_normal, my_normal);
		if (d < bestd && similarity > 0.8) {
			bestd = d;
			otheri = i;
			best_similarity = similarity;
			best_position = t_position;
		}
	}
	
	// if good correspondence record weight and id
	if (otheri > -1) {
		neighbor.id = otheri;
		neighbor.weight = 1.0/(sqrt(bestd) + 1.0);
	} else {
		neighbor.id = -1;
		neighbor.weight = 0;
	}
		
	mat3 cov = neighbor.weight * outerProduct(my_position, best_position);
	vec3 my_avg_trans = neighbor.weight * my_position;
	fragColor = vec4(cov[0], my_avg_trans.x);
	fragColor1 = vec4(cov[1], my_avg_trans.y);
	fragColor2 = vec4(cov[2], my_avg_trans.z);
	fragColor3 = neighbor.weight * vec4(best_position, 1);
	fragColor4 = vec4(neighbor.id, best_position);

}