#include "CCamera.hpp"

CCamera::CCamera() {
	position = glm::vec3(CHUNK_XSIZE / 2.0 + 0.5, CHUNK_YSIZE / 2.0 + 0.5, CHUNK_ZSIZE / 2.0 + 0.5);
	angle = glm::vec3(-60.0, 0.0, -45.0);

	iCameraKeys = 0;
	fCameraRotation = 0.0;

	CEventManager::instance()->subscribe(this);
}

void CCamera::update() {
	float fTimeStep = CClock::instance()->getTimeStep();
	glm::vec2 direction(0.0, 0.0);

	// XY Friction.
	glm::vec2 velXY(velocity.x, velocity.y);
	float dist = glm::length(velXY);
	if (dist <= CCAMERA_FRICTION*fTimeStep) {
		velXY = glm::vec2(0.0, 0.0);
	}
	else {
		velXY -= glm::normalize(velXY) * CCAMERA_FRICTION * fTimeStep;
	}
	velocity = glm::vec3(velXY.x, velXY.y, velocity.z);

	// Get acceleration from direction keys.
	if (iCameraKeys & CCAMERA_UP) { direction.y += 1.0; }
	if (iCameraKeys & CCAMERA_LEFT) { direction.x -= 1.0; }
	if (iCameraKeys & CCAMERA_DOWN) { direction.y -= 1.0; }
	if (iCameraKeys & CCAMERA_RIGHT) { direction.x += 1.0; }
	if (glm::length(direction) > 1.0) {
		direction = glm::normalize(direction);
	}

	float r = angle.z * (M_PI / 180.0);
	glm::mat2 rotationMat(cos(r), -sin(r), sin(r), cos(r));
	direction = rotationMat * direction;
	direction *= CCAMERA_ACCELERATION;

	// Add in acceleration.
	acceleration = glm::vec3(direction.x, direction.y, acceleration.z);
	velocity += acceleration * fTimeStep;

	// Limit speed.
	velXY = glm::vec2(velocity.x, velocity.y);
	dist = glm::length(velXY);
	if (dist > CCAMERA_MAXVELOCITY) {
		velXY = glm::normalize(velXY) * CCAMERA_MAXVELOCITY;
		velocity = glm::vec3(velXY.x, velXY.y, velocity.z);
	}

	position += velocity * fTimeStep;

	dist = glm::min((float)CCAMERA_ROTATIONSPEED*fTimeStep, abs(fCameraRotation));
	if (fCameraRotation <= 0.0) {
		angle.z -= dist;
		fCameraRotation += dist;
	}
	else {
		angle.z += dist;
		fCameraRotation -= dist;
	}
	while (angle.z < 0.0) { angle.z += 360.0; }
	while (angle.z > 360.0) { angle.z -= 360.0; }
}

void CCamera::positionCamera() {
	glLoadIdentity();
	glRotatef(angle.x, 1.0, 0.0, 0.0);
	glRotatef(angle.z, 0.0, 0.0, 1.0);
	glTranslatef(-position.x, -position.y, -position.z);
}

void CCamera::setCameraPosition(float x, float y, float z, int angle) {

}

void CCamera::refreshCamera(int iWidth, int iHeight) {
	this->notify(&CSDLManagerEVENTWindowEventResize(iWidth, iHeight));
}

void CCamera::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_keydown")) {
		CSDLManagerEVENTKeyDown *request = (CSDLManagerEVENTKeyDown *)e;
		iCameraKeys |= (request->getKey() == SDLK_w ? CCAMERA_UP : 0);
		iCameraKeys |= (request->getKey() == SDLK_a ? CCAMERA_LEFT : 0);
		iCameraKeys |= (request->getKey() == SDLK_s ? CCAMERA_DOWN : 0);
		iCameraKeys |= (request->getKey() == SDLK_d ? CCAMERA_RIGHT : 0);
		if (request->getKey() == SDLK_q) { fCameraRotation -= 90.0; }
		if (request->getKey() == SDLK_e) { fCameraRotation += 90.0; }
	}
	else if (e->compareType("event_sdlmanager_keyup")) {
		CSDLManagerEVENTKeyUp *request = (CSDLManagerEVENTKeyUp *)e;
		iCameraKeys &= ~(request->getKey() == SDLK_w ? CCAMERA_UP : 0);
		iCameraKeys &= ~(request->getKey() == SDLK_a ? CCAMERA_LEFT : 0);
		iCameraKeys &= ~(request->getKey() == SDLK_s ? CCAMERA_DOWN : 0);
		iCameraKeys &= ~(request->getKey() == SDLK_d ? CCAMERA_RIGHT : 0);
	}
	else if (e->compareType("event_sdlmanager_windoweventresize")) {
		CSDLManagerEVENTWindowEventResize *request = (CSDLManagerEVENTWindowEventResize *)e;
		fWindowWidth = request->getWidth() / 16.0;
		fWindowHeight = request->getHeight() / 16.0;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glViewport(0, 0, request->getWidth(), request->getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-fWindowWidth, fWindowWidth, -fWindowHeight, fWindowHeight, -256.0, 256.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

CCamera *CCamera::instance() {
	static CCamera *inst = 0;
	if (!inst) {
		inst = new CCamera();
	}
	return inst;
}