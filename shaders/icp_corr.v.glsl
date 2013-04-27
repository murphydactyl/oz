uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform int modelSize;
uniform int otherModelSize;
uniform float D_THRESH;
in vec3 v_position;
uniform sampler2D u_position;
out struct PerVertex {
	float id;
	float weight;
	
} neighbor;

void main(void) {
	vec3 r = (m * vec4(v_position, 1)).xyz;
	float bestd = 100000;
	int otheri = -1;
	for (int i = 0; i < otherModelSize; i++) {
		vec4 t = texelFetch(u_position, ivec2(i, 0), 0);
		float d = distance(t.xyz, r);
		if (d < bestd) {
			bestd = d;
			otheri = i;
		}
	}


	// compute frag coord of winner
	// 1D coordinate since we are just using first row of 2D viewport
	// frag coord needs to be in normalized coords so in x \in [-1,1];
	float x = float(gl_VertexID + 0.5) / (modelSize / 2.0) - 1;

	// if good correspondence record weight and id
	if (bestd <= D_THRESH) {
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