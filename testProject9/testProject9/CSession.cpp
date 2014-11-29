#include "CSession.hpp"
#include "CClock.hpp"
#include "CRenderableVoxelChunk.hpp"

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

	chunk->update();

	while (bRunning) {
		iFrameStart = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		sdlManager->sdlEventHandle();

		clock->updateClock(iFrameDelay);

		glRotatef(-60.0, 1.0, 0.0, 0.0);
		glRotatef(clock->getCurrentTime()*10.0, 0.0, 0.0, 1.0);
		glTranslatef(-32.5, -32.5, -32.5);
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
	else if (e->compareType("event_sdlmanager_windoweventresize")) {
		CSDLManagerEVENTWindowEventResize *request = (CSDLManagerEVENTWindowEventResize *)e;
		float fWindowWidth = request->getWidth() / 16.0;
		float fWindowHeight = request->getHeight() / 16.0;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glViewport(0, 0, request->getWidth(), request->getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-fWindowWidth, fWindowWidth, -fWindowHeight, fWindowHeight, -128.0, 128.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}