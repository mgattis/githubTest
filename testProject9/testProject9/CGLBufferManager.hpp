#ifndef _CGLBUFFERMANAGER_HPP
#define _CGLBUFFERMANAGER_HPP

#include "main.hpp"
#include "CGLShaderManager.hpp"
#include "CGLBuffer.hpp"
using namespace std;

class CGLBufferManager {
private:
	map<string, CGLBuffer *> bufferList;

	CGLBufferManager();

public:
	~CGLBufferManager();

	CGLBuffer *get(string name);
	bool exist(string name);
	//bool load(std::string name, CGLBuffer *buffer);
	bool remove(string name);
	bool add(string name, CGLBuffer *buffer);
	bool forceadd(std::string name, CGLBuffer *buffer);

	static CGLBufferManager *instance();
};

#endif /* !_CGLBUFFERMANAGER_HPP */