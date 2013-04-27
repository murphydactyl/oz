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
	vec4 center = m * vec4(model.xyz, 1);
	vec3 dir = (vec4(my_position,1) - center).xyz;
	vec3 dirn = normalize(dir);
	vec3 best_position = center.xyz + model.w * dirn;
	float bestd = abs(length(dir) - model.w);
	float similarity = dot(my_normal, dirn);
	// if good correspondence record weight and id
	if (bestd < 50) {
		neighbor.id = 0;
		neighbor.weight = 1.0/(sqrt(bestd) + 1.0);

		mat3 cov = neighbor.weight * outerProduct(my_position, best_position);
		vec3 my_avg_trans = neighbor.weight * my_position;
		fragColor = vec4(cov[0], my_avg_trans.x);
		fragColor1 = vec4(cov[1], my_avg_trans.y);
		fragColor2 = vec4(cov[2], my_avg_trans.z);
		fragColor3 = neighbor.weight * vec4(best_position, 1);
		fragColor4 = vec4(neighbor.id, best_position);

	} else {
		neighbor.id = -1;
		neighbor.weight = 0;
	}
		
}