
precision mediump float;

uniform sampler2D tex;

varying vec2 v_TexCoordinate;

void main() {
	gl_FragColor = texture2D(tex, v_TexCoordinate);
}
