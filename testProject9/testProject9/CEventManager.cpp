#include "CEventManager.hpp"

CEventManager::CEventManager() {
	clog << "[INFO] <CEventManager>: Instance created." << endl;
}

CEventManager::~CEventManager() {

}

void CEventManager::subscribe(IEventable *eventable) {
	if (hasEventable(eventable)) {
		clog << "[INFO] Eventable already subscribed." << endl;
	}
	else {
		subscribed[eventable] = eventable;
	}
}

void CEventManager::unsubscribe(IEventable *eventable) {
	if (hasEventable(eventable)) {
		subscribed.erase(eventable);
	}
}

bool CEventManager::hasEventable(IEventable *eventable) {
	if (subscribed.count(eventable)) {
		return true;
	}
	return false;
}

void CEventManager::post(IEvent *e) {
	map<IEventable *, IEventable *>::iterator it = subscribed.begin();
	for (; it != subscribed.end(); ++it) {
		it->second->notify(e);
	}
}

CEventManager *CEventManager::instance() {
	static CEventManager *inst = 0;
	if (!inst) {
		inst = new CEventManager();
	}
	return inst;
}