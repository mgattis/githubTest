#ifndef _CLOCATION_HPP
#define _CLOCATION_HPP

#include "main.hpp"

class CLocation {
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec3 angle;

	CLocation();
	CLocation(glm::vec2 postion);
	CLocation(float x, float y);

	void setPosition(glm::vec2 position) { this->position = position; }
	void setPosition(float x, float y) { this->position.x = x; this->position.y = y; }
	void setVelocity(glm::vec2 velocity) { this->velocity = velocity; }
	void setVelocity(float x, float y) { this->velocity.x = x; this->velocity.y = y; }
	void setAcceleration(glm::vec2 acceleration) { this->acceleration = acceleration; }
	void setAcceleration(float x, float y) { this->acceleration.x = x; this->acceleration.y = y; }
	void setAnglePosition(float anglePosition) { this->angle.x = anglePosition; }
	void setAngleVelocity(float angleVelocity) { this->angle.y = angleVelocity; }
	void setAngleAcceleration(float angleAcceleration) { this->angle.z = angleAcceleration; }

	void zero();

	void copy(CLocation location);
};

#endif /* !_CLOCATION_HPP */