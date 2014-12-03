#ifndef _CCAMERA_HPP
#define _CCAMERA_HPP
#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CLocation.hpp"
#include "CClock.hpp"
#include "main.hpp"
#define CCAMERA_FRICTION		(64.0f * 4.0f)
#define CCAMERA_MAXVELOCITY		(64.0f)
#define CCAMERA_ACCELERATION	(64.0f * 8.0f)
#define CCAMERA_ROTATIONSPEED	(360.0)

enum CCAMERA_KEYS {
	CCAMERA_UP = 1,
	CCAMERA_LEFT = 2,
	CCAMERA_DOWN = 4,
	CCAMERA_RIGHT = 8,
};

class CCamera : public IEventable, public CLocation {
private:
	float fWindowWidth;
	float fWindowHeight;
	int iCameraKeys;
	float fCameraRotation;

	CCamera();

public:
	void update();
	void positionCamera();

	void setCameraPosition(float x, float y, float z, int angle);
	void refreshCamera(int iWidth, int iHeight);

	void notify(IEvent *e);
	static CCamera *instance();
};

#endif