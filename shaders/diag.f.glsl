#define SQRT2OVER2 0.707106781186547
layout(pixel_center_integer) in vec4 gl_FragCoord;
out vec4 fragColor;
out vec4 fragColor1;
out vec4 fragColor2;
out vec4 fragColor3;
uniform mat4 A;
void main(void) {

	mat4 D, Q, J;
	
	D = A;

	Q[0] = vec4(1, 0, 0, 0);
	Q[1] = vec4(0, 1, 0, 0);
	Q[2] = vec4(0, 0, 1, 0);
	Q[3] = vec4(0, 0, 0, 1);
	J = Q;
	
	int maxit = 3;
	float theta, s, c;
	for (int k = 0; k < maxit; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 4; j++) {
				float d = D[j][i];
				if (d == 0) break;
				float b = D[j][j];
				float a = D[i][i];
				if (b == a) {
					s = SQRT2OVER2;
					c = SQRT2OVER2;
				} else {
					theta = atan(2 * d, b - a) / 2.0;
					s = sin(theta);
					c = cos(theta);
				}
				J[i][i] = c;
				J[j][i] = s;
				J[i][j] = -s;
				J[j][j] = c;
				D = transpose(J) * D * J;
				Q = Q * J;
				J[i][i] = 1.0; J[j][j] = 1.0;
				J[i][j] = 0.0; J[j][i] = 0.0;
			}
		}
		float offdiag = abs(D[0][1]) + abs(D[0][2]) + abs(D[0][3]) + abs(D[1][2]) + abs(D[1][3]) + abs(D[2][3]);
		if (offdiag < 1e-4) break;
	}
	fragColor = Q[0];
	fragColor1 = Q[1];
	fragColor2 = Q[2];
	fragColor3 = Q[3];
}