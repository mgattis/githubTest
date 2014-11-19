#ifndef _IVOXELBUFFER_HPP
#define _IVOVELBUFFER_HPP
#include "main.hpp"

class IVoxelBuffer {
private:
	unsigned char *ucVoxelBuffer;
	int iChanges;
	int iVoxelCount;

public:
	IVoxelBuffer();
	~IVoxelBuffer();

	int getVoxelType(int iXPos, int iYPos, int iZPos);
	void setVoxelType(int iXPos, int iYPos, int iZPos, int iVoxelType);

	unsigned char *getVoxelBuffer() { return ucVoxelBuffer; }

	int getVoxelCount() { return iVoxelCount; }
	int getChanges() { return iChanges; }
	void resetChanges() { iChanges = 0; }
};

#endif