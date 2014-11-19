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

	int getVoxelType(int iX, int iY, int iZ);
	void setVoxelType(int iX, int iY, int iZ, int iVoxelType);

	unsigned char *getVoxelArray() { return ucVoxelBuffer; }

	int getVoxelCount() { return iVoxelCount; }
	int getChanges() { return iChanges; }
	void resetChanges() { iChanges = 0; }
};

#endif