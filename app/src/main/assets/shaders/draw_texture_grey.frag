
precision mediump float;

uniform sampler2D tex;

varying vec2 v_TexCoordinate;

void main() {
    vec4 color = texture2D(tex, v_TexCoordinate);
    float luminance = 0.3 * color.x + 0.5 * color.y + 0.2 * color.z;
	gl_FragColor = vec4(luminance);
}
