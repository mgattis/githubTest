#include "CLocation.hpp"

CLocation::CLocation() {
	position = glm::vec3(0.0, 0.0, 0.0);
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

CLocation::CLocation(glm::vec3 position) {
	this->position = position;
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

CLocation::CLocation(float x, float y, float z) {
	position = glm::vec3(x, y, z);
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

void CLocation::zero() {
	position = glm::vec3(0.0, 0.0, 0.0);
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);
	angle = glm::vec3(0.0, 0.0, 0.0);
}

void CLocation::copy(CLocation location) {
	this->position = location.position;
	this->velocity = location.velocity;
	this->acceleration = location.acceleration;
	this->angle = location.angle;
}