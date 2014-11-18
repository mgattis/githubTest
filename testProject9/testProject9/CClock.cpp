#include "CClock.hpp"

CClock::CClock() {
	fCurrentTime = 0.0;
	fTimeStep = 0.0;
	fSpeed = 1.0;
}

void CClock::updateClock(int iFrameDelay) {
	fTimeStep = (float)iFrameDelay / 1000.0;
	fTimeStep *= fSpeed;

	fCurrentTime += fTimeStep;
}

CClock *CClock::instance() {
	static CClock *inst = NULL;
	if (!inst) {
		inst = new CClock();
	}
	return inst;
}