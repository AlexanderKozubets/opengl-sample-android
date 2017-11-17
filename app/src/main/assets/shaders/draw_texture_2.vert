
attribute vec4 vPosition;

varying vec2 v_TexCoordinate;

uniform mat4 uMVPMatrix;

void main() {
    v_TexCoordinate = vPosition.st;
	gl_Position = uMVPMatrix * vPosition;
}
