uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec4 model;
uniform mat3 inv_trans_3x3_m;
uniform mat3 inv_3x3_m;
uniform mat3 trans_3x3_m;
uniform mat3 _3x3_m;
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

vec3 pt2Plane(vec3 q, vec3 p0, vec3 n, vec3 S) {
	vec3 p = q - p0;
	return clamp(p - n * dot(n,p), -S, S) + p0;
}

void main(void) {
	ivec2 fCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	vec3 my_position = (texelFetch(o_position, fCoord, 0)).xyz;
	vec3 best_position;
	
	if (length(my_position - m[3].xyz) < length(model.xyz)) {
		vec3 my_normal = trans_3x3_m * normalize(texelFetch(o_normal, fCoord, 0).xyz);
		float bestd = D_THRESH;
		vec3 S = model.xyz;
		vec3 U = inv_3x3_m * (my_position - (m[3]).xyz);
		
		if (my_normal.x > 0) {
			vec3 pX = pt2Plane(U, vec3(+S.x, 0, 0), vec3(+1, 0, 0), S);
			float pXd = distance(U, pX);
			if (pXd < bestd) {
				bestd = pXd;
				best_position = pX;
			}
		} else if (my_normal.x < 0) {
			vec3 nX = pt2Plane(U, vec3(-S.x, 0, 0), vec3(-1, 0, 0), S);
			float nXd = distance(U, nX);
			if (nXd < bestd) {
				bestd = nXd;
				best_position = nX;
			}
		}
		
		if (my_normal.y > 0) {
			vec3 pY = pt2Plane(U, vec3(0, +S.y, 0), vec3(0, +1, 0), S);
			float pYd = distance(U, pY);
			if (pYd < bestd) {
				bestd = pYd;
				best_position = pY;
			}
		} else if (my_normal.y < 0) {
			vec3 nY = pt2Plane(U, vec3(0, -S.y, 0), vec3(0, -1, 0), S);
			float nYd = distance(U, nY);
			if (nYd < bestd) {
				bestd = nYd;
				best_position = nY;
			}
		}
		
		if (my_normal.z > 0) {
			vec3 pZ = pt2Plane(U, vec3(0, 0, +S.z), vec3(0, 0, +1), S);
			float pZd = distance(U, pZ);
			if (pZd < bestd) {
				bestd = pZd;
				best_position = pZ;
			}
		} else if (my_normal.z < 0) {
			vec3 nZ = pt2Plane(U, vec3(0, 0, -S.z), vec3(0, 0, -1), S);
			float nZd = distance(U, nZ);
			if (nZd < bestd) {
				bestd = nZd;
				best_position = nZ;
			}
		}

		
		if (bestd < D_THRESH) {
			best_position = (m * vec4(best_position, 1)).xyz;
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
	} else {
		neighbor.id = -1;
		neighbor.weight = 0;
	}

	fragColor4 = vec4(neighbor.id, best_position);

}

