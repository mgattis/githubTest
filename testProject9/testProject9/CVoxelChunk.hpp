#ifndef _IVOXELCHUNK_HPP
#define _IVOXELCHUNK_HPP
#include "main.hpp"
#include "IVoxelBuffer.hpp"
#include "IVoxel.hpp"

class CVoxelChunk {
private:
	IVoxelBuffer *voxelBuffer;
	IVoxel *voxels;

	int iXPos;
	int iYPos;
	int iZPos;

public:
	CVoxelChunk();
	CVoxelChunk(int iXPos, int iYPos, int iZPos);

	void setCooridnates(int iXPos, int iYPos, int iZPos);

	int getXPos() { return iXPos; }
	int getYPos() { return iYPos; }
	int getZPos() { return iZPos; }

	IVoxel *getVoxel(int iXPos, int iYPos, int iZPos);

	IVoxel *getAllVoxels() { return voxels; }
	IVoxelBuffer *getVoxelBuffer() { return voxelBuffer; }
};

#endif /* !_IVOXELCHUNK_HPP */