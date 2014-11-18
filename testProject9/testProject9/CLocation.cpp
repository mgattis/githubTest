#include "CLocation.hpp"

CLocation::CLocation() {
	position = glm::vec2(0.0, 0.0);
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

CLocation::CLocation(glm::vec2 position) {
	this->position = position;
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

CLocation::CLocation(float x, float y) {
	position = glm::vec2(x, y);
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

void CLocation::zero() {
	position = glm::vec2(0.0, 0.0);
	velocity = glm::vec2(0.0, 0.0);
	acceleration = glm::vec2(0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

void CLocation::copy(CLocation location) {
	this->position = location.position;
	this->velocity = location.velocity;
	this->acceleration = location.acceleration;
	this->angle = location.angle;
}