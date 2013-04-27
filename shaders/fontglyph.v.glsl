uniform uint width;
uniform uint height;
in vec4 coord;
out vec2 texcoord;

void main(void) {
	float x = coord.x / (width / 2.0) - 1;
	float y = coord.y / (height / 2.0) - 1;
  gl_Position = vec4(x,y, 0, 1);
  texcoord = coord.zw;
}