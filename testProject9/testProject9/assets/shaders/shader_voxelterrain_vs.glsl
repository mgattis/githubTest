in vec3 vertex3f;
in vec3 normal3f;

out vec3 vertex;
out vec3 normal;

void main() {
	vertex = vertex3f;
	normal = normal3f;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex3f, 1.0);
}