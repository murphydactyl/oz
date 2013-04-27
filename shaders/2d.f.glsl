in vec4 f_color;
out vec4 fragColor;
void main(void) {
  fragColor = vec4(f_color.x, f_color.y, f_color.z, f_color.w);
}
