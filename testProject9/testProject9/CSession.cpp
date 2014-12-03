#include "CSession.hpp"
#include "CClock.hpp"
#include "CRenderableVoxelChunk.hpp"
#include "CCamera.hpp"

CSession::CSession() {
	eventManager = CEventManager::instance();
	sdlManager = CSDLManager::instance();

	iFrameDelay = 16;
	bRunning = true;

	eventManager->subscribe(this);
}

void CSession::run() {
	CClock *clock = CClock::instance();
	CGLBuffer *glBuffer = new CGLBuffer();
	CRenderableVoxelChunk *chunk = new CRenderableVoxelChunk(0, 0, 0, NULL);
	CCamera *camera = CCamera::instance();

	chunk->update();
	camera->refreshCamera(800, 600);

	while (bRunning) {
		iFrameStart = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		sdlManager->sdlEventHandle();

		clock->updateClock(iFrameDelay);

		camera->update();
		camera->positionCamera();
		chunk->draw();

		glUseProgram(0);
		glClear(GL_DEPTH_BUFFER_BIT);
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(CHUNK_XSIZE, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, CHUNK_YSIZE, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 2.0);
		glVertex3f(0.0, 0.0, CHUNK_ZSIZE);
		glEnd();
		
		sdlManager->swapBuffers();
		iFrameEnd = SDL_GetTicks();
		if (iFrameDelay - (iFrameEnd - iFrameStart) > 0) {
			SDL_Delay(iFrameDelay - (iFrameEnd - iFrameStart));
		}
		iFrameDelay = iFrameEnd - iFrameStart;
		iFrameDelay = iFrameDelay < 16 ? 16 : iFrameDelay;
	}
}

void CSession::drawScene() {
	// Do nothing for now.
}

void CSession::notify(IEvent *e) {
	if (e->compareType("event_sdlmanager_quit")) {
		bRunning = false;
	}
}