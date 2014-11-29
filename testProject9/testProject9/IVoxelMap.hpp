#ifndef _IVOXELMAP_HPP
#define _IVOXELMAP_HPP
#include "CVoxelChunk.hpp"
#include "main.hpp"

class IVoxelMap {
public:
	IVoxelMap();
	
	virtual CVoxelChunk *getChunk(int iX, int iY, int iZ) = 0;
};

#endif