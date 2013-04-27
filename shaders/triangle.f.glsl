in vec3 C;
out vec4 fragColor;
void main(void) {
  fragColor = vec4(C.xyz, 1.0);
}
