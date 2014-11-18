#ifndef _CCLOCK_HPP
#define _CCLOCK_HPP
#include "main.hpp"

class CClock {
private:
	float fCurrentTime;
	float fTimeStep;
	float fSpeed;

	CClock();

public:
	float getCurrentTime() { return fCurrentTime; }
	float getTimeStep() { return fTimeStep; }
	
	void setSpeed(float fSpeed) { this->fSpeed = fSpeed; }
	float getSpeed() { return fSpeed; }

	void updateClock(int iFrameDelay);

	static CClock *instance();
};

#endif /* !_CCLOCK_HPP */