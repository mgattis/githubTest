in vec3 vertex3f;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex3f, 1.0);
}