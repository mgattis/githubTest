#ifndef _CGLSHADERMANAGER_HPP
#define _CGLSHADERMANAGER_HPP

#include "main.hpp"
#include "CGLShader.hpp"
using namespace std;

class CGLShaderManager {
private:
	map<string, CGLShader *> shaderList;

	CGLShaderManager();

public:
	~CGLShaderManager();

	CGLShader *get(string name);
	bool exist(string name);
	bool load(string name);
	bool remove(string name);
	void add(string name, CGLShader *shader);

	static CGLShaderManager *instance();
};

#endif /* !_CGLSHADERMANAGER_HPP */