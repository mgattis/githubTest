#ifndef _CEVENTMANAGER_HPP
#define _CEVENTMANAGER_HPP

#include <iostream>
#include <string>
#include <map>
using namespace std;

class IEvent {
protected:
	string type;
public:
	IEvent() { type = ""; }
	IEvent(string type) { this->type = type; }
	string getType() { return type; }
	bool compareType(std::string type) {
		if (this->type.compare(type) == 0) {
			return true;
		}
		return false;
	}
};

class IEventable {
public:
	virtual void notify(IEvent *e) = 0;
};

class CEventManager {
private:
	map<IEventable *,IEventable *> subscribed;
	CEventManager();
public:
	~CEventManager();
	void subscribe(IEventable *eventable);
	void unsubscribe(IEventable *eventable);
	void post(IEvent *e);
	static CEventManager *instance();
	bool hasEventable(IEventable *eventable);
};

#endif /* !_CEVENTMANAGER_HPP */