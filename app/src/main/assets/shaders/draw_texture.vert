
attribute vec4 vPosition;

attribute vec2 vTexCoord;

varying vec2 v_TexCoordinate;

void main() {
    v_TexCoordinate = vTexCoord;
	gl_Position = vPosition;
}
