
attribute vec4 vPosition;

varying vec2 v_TexCoordinate;

void main() {
    v_TexCoordinate = vPosition.st;
	gl_Position = vPosition;
}
