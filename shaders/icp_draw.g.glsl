uniform mat4 v;
uniform mat4 p;
layout(points) in;
layout(line_strip) out;
layout(max_vertices = 2) out;

in VertexData {
	vec4 N;
} vertex[];
out vec4 C;

void main() {
	
	if (vertex[0].N.w == 0) {
		EndPrimitive();
	} else {
		
		vec4 pos = gl_in[0].gl_Position;
		if (pos.z == 0 && pos.x == 0 && pos.y == 0 && pos.w != 0) {
			C = vec4(0, 1, 1, 1);
		} else {
			C = vec4(1,0,0,1);
		}
		gl_Position = p * v * gl_in[0].gl_Position;
		EmitVertex();
		
		C = vec4(1,1,0,1);
		gl_Position = p * v * vertex[0].N;
		EmitVertex();

		EndPrimitive();
	}

}