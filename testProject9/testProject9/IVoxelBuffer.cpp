#include "IVoxelBuffer.hpp"
#include <stdio.h>
#include <stdlib.h>

IVoxelBuffer::IVoxelBuffer() {
	ucVoxelBuffer = (unsigned char *)calloc(64 * 64 * 64, sizeof(unsigned char));
	iChanges = 0;
	iVoxelCount = 0;
}

IVoxelBuffer::~IVoxelBuffer() {
	free(ucVoxelBuffer);
}

int IVoxelBuffer::getVoxelType(int iX, int iY, int iZ) {
	int iVoxelOffset = iX + iY * 64 + iZ * 4096;
	
	if (iVoxelOffset < 0) { return 0; }
	if (iVoxelOffset > 262143) { return 0; }

	return ucVoxelBuffer[iVoxelOffset];
}

void IVoxelBuffer::setVoxelType(int iX, int iY, int iZ, int iVoxelType) {
	int iVoxelOffset = iX + iY * 64 + iZ * 4096;
	int iOldType = 0;

	if (iVoxelOffset < 0) { return; }
	if (iVoxelOffset > 262143) { return; }

	iOldType = ucVoxelBuffer[iVoxelOffset];
	iVoxelType &= 0xFF;
	if (iOldType != iVoxelType) {
		ucVoxelBuffer[iVoxelOffset] = iVoxelType;
		iChanges++;

		if (iVoxelType == 0) {
			iVoxelCount--;
		}
		else {
			iVoxelCount++;
		}
	}
}


