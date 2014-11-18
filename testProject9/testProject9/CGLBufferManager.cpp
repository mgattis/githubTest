#include "CGLBufferManager.hpp"

// CGLBufferManager manages GLBuffer objects, and makes them availiable to the rest of the program.
CGLBufferManager::CGLBufferManager() {
	clog << "[INFO] <CGLBufferManager>: Instance created." << endl;
}

// Gets a buffer from the list. If it does not exist, it attempts to load and return it.
CGLBuffer *CGLBufferManager::get(string name) {
	if (exist(name)) {
		return bufferList[name];
	}
	return NULL;
}

// Checks to see if there is a buffer by the given name in the list.
bool CGLBufferManager::exist(string name) {
	if (bufferList.count(name)) {
		return true;
	}
	return false;
}

// Loads a buffer into the list from a Json file.
/*bool CGLBufferManager::load(std::string name, CGLBuffer *glBuffer) {
	if (!exist(name)) {
		bufferList[name] = glBuffer;
		return true;
	}
	return false;
}*/

// If it exist, removes the buffer from the list by the given name.
bool CGLBufferManager::remove(string name) {
	if (exist(name)) {
		bufferList.erase(name);
		return true;
	}
	return false;
}

// Add a manually created buffer object.
bool CGLBufferManager::add(string name, CGLBuffer *buffer) {
	if (!exist(name)) {
		bufferList[name] = buffer;
		return true;
	}
	return false;
}

bool CGLBufferManager::forceadd(std::string name, CGLBuffer *buffer) {
	if (!exist(name)) {
		bufferList[name] = buffer;
		return true;
	}
	remove(name);
	bufferList[name] = buffer;
	return true;
}

// Singleton, only one instance of this class my exist.
// This is to reduce duplicate resources on the GFX card.
CGLBufferManager *CGLBufferManager::instance() {
	static CGLBufferManager *inst = NULL;
	if (!inst) {
		inst = new CGLBufferManager();
	}
	return inst;
}
