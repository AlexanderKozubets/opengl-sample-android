
attribute vec4 vPosition;

attribute vec4 vColor;

varying vec4 v_Color;

uniform mat4 uMVPMatrix;

void main() {
    v_Color = vColor;
	gl_Position = uMVPMatrix * vPosition;
}
