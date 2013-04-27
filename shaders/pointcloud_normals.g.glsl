uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
layout(points) in;
layout(line_strip) out;
layout(max_vertices = 2) out;

in VertexData {
	vec3 C;
	vec3 N;
} vertex[];
out vec4 C;

void main() {
	
	if (length(vertex[0].N) == 0) {
		EndPrimitive();
	} else {
		C = vec4(1,1,1,1);
		gl_Position = p * v * m * gl_in[0].gl_Position;
		EmitVertex();
		
		C = vec4(vertex[0].N,1);
		gl_Position = p * v * m * vec4(gl_in[0].gl_Position.xyz + 5 * vertex[0].N, 1.0);
		EmitVertex();
		
		EndPrimitive();
	}
}