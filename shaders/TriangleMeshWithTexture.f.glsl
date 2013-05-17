uniform sampler2D tex;
in vec2 f_texcoord;
out vec4 fragColor;
layout(pixel_center_integer) in vec4 gl_FragCoord;
void main(void) {
    vec4 t = texture(tex, f_texcoord);
    fragColor = t;
}
