#ifndef _CRENDERABLEVOXELCHUNK_HPP
#define _CRENDERABLEVOXELCHUNK_HPP
#include "CVoxelChunk.hpp"
#include "IVoxelMap.hpp"
#include "CGLBuffer.hpp"
#include "CGLShaderManager.hpp"
#include "CGLShader.hpp"

class CRenderableVoxelChunk : public CVoxelChunk {
private:
	IVoxelMap *map;
	CGLBuffer *glBuffers[2];
	int iRenderBuffer;

	unsigned char getWorldVoxel(int iX, int iY, int iZ);
	CGLBuffer *getDrawGLBuffer();
	CGLBuffer *getBuildGLBuffer();

public:
	CRenderableVoxelChunk();
	CRenderableVoxelChunk(int iX, int iY, int iZ, IVoxelMap *map);

	void checkForBuild();
	void build();

	void update();
	void draw();

	void initialize();
};

#endif