uniform sampler2D tex;
in vec2 texcoord;
out vec4 fragColor;

void main(void) {
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	float bitmap = texture(tex, texcoord).r;
  fragColor = vec4(1, 0, 0, bitmap) * color;
}