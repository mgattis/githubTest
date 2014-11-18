#include "CEventManager.hpp"
#include "CSDLManager.hpp"
#include "CSession.hpp"
#include "CClock.hpp"
#include "main.hpp"

int main(int argc, char **argv) {
	CEventManager::instance();
	CSDLManager::instance();
	CClock::instance();
	CSession *session = new CSession();

	session->run();

	return 0;
}