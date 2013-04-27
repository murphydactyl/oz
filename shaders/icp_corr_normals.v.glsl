uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 inv_trans_3x3_m;
uniform int modelSize;
uniform int otherModelSize;
uniform float D_THRESH;
in vec3 v_position;
in vec3 v_normal;
uniform sampler2D u_position;
uniform sampler2D u_normal;
out struct PerVertex {
	float id;
	float weight;
} neighbor;

void main(void) {
	vec3 r_position = (m * vec4(v_position, 1)).xyz;
	vec3 r_normal = normalize(inv_trans_3x3_m * v_normal);
	float bestd = D_THRESH;
	int otheri = -1;
	float best_similarity = -1;
	for (int i = 0; i < otherModelSize; i++) {
		vec3 t_position = texelFetch(u_position, ivec2(i, 0), 0).xyz;
		vec3 t_normal = normalize(texelFetch(u_normal, ivec2(i, 0), 0).xyz);
		float d = distance(t_position, r_position);
		float similarity = dot(t_normal, r_normal);
		if (d < bestd && similarity > .8) {
			bestd = d;
			otheri = i;
			best_similarity = similarity;
		}
	}
	
	// compute frag coord of winner
	// 1D coordinate since we are just using first row of 2D viewport
	// frag coord needs to be in normalized coords so in x \in [-1,1];
	float x = float(gl_VertexID + 0.5) / (modelSize / 2.0) - 1;

	// if good correspondence record weight and id
	if (otheri > -1) {
		neighbor.id = otheri;
		neighbor.weight = 1.0/(bestd + 1.0);
	} else {
		neighbor.id = -1;
		neighbor.weight = 0;
	}
	
	// set frag coordinate
	gl_Position = vec4(x,0,0,1.0);
	gl_PointSize = 1.0;
}