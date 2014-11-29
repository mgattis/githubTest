#ifndef _CVOXELCHUNK_HPP
#define _CVOXELCHUNK_HPP
#include "main.hpp"

typedef struct _SLocation {
	int iX;
	int iY;
	int iZ;
}SLocation;

class CVoxelChunk {
protected:
	unsigned char *voxelList;
	SLocation chunkLocation;
	int iVoxelCount;
	int iEditCount;

public:
	CVoxelChunk();
	CVoxelChunk(int iX, int iY, int iZ);
	
	void setChunkLocation(int iX, int iY, int iZ);
	void setChunkLocation(SLocation chunkLocation) { this->chunkLocation = chunkLocation; }

	int getX() { return chunkLocation.iX; }
	int getY() { return chunkLocation.iY; }
	int getZ() { return chunkLocation.iZ; }
	SLocation getChunkLocation() { return chunkLocation; }

	unsigned char getVoxel(int iX, int iY, int iZ);
	unsigned char getVoxel(SLocation voxelLocation);

	void setVoxel(int iX, int iY, int iZ, int iType);
	void setVoxel(SLocation voxelLocation, int iType);
};

#endif