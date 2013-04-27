in vec4 C;
out vec4 fragColor;
void main(void) {
  fragColor = vec4(C.xyz, 0.5);
}
