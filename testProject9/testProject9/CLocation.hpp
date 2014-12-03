#ifndef _CLOCATION_HPP
#define _CLOCATION_HPP

#include "main.hpp"

class CLocation {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 angle;

	CLocation();
	CLocation(glm::vec3 postion);
	CLocation(float x, float y, float z);

	void setPosition(glm::vec3 position) { this->position = position; }
	void setPosition(float x, float y, float z) { this->position = glm::vec3(x, y, z); }
	void setVelocity(glm::vec3 velocity) { this->velocity = velocity; }
	void setVelocity(float x, float y, float z) { this->velocity = glm::vec3(x, y, z); }
	void setAcceleration(glm::vec3 acceleration) { this->acceleration = acceleration; }
	void setAcceleration(float x, float y, float z) { this->acceleration = glm::vec3(x, y, z); }
	void setAngle(glm::vec3 angle) { this->angle = angle; }
	void setAngle(float x, float y, float z) { this->angle = glm::vec3(x, y, z); }

	void zero();

	void copy(CLocation location);
};

#endif /* !_CLOCATION_HPP */