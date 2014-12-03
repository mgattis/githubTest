in vec3 normal;

void main() {
	vec3 light = normalize(vec3(1.0, 0.75, 0.5));
	float intensity = dot(normal, light);
	intensity = clamp(intensity, 0.0, 1.0);
	vec3 color = mix(vec3(0.25, 0.25, 0.25), vec3(1.0, 1.0, 1.0), intensity);

	gl_FragColor = vec4(color, 1.0);
}
