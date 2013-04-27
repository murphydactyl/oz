in vec3 f_color;
out vec4 fragColor;

void main(void) {
  fragColor = vec4(f_color.x, f_color.x, f_color.x, 1.0);
}