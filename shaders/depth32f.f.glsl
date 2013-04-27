in vec4 view_position;
out vec4 fragColor;

void main(void) {
  float d = -view_position.z;
  fragColor = vec4(d, 0, 0, 1.0);
}