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

int IVoxelBuffer::getVoxelType(int iXPos, int iYPos, int iZPos) {
	int iVoxelOffset = iXPos + iYPos * 64 + iZPos * 4096;
	
	if (iVoxelOffset < 0) { return 0; }
	if (iVoxelOffset > 262143) { return 0; }

	return ucVoxelBuffer[iVoxelOffset];
}

void IVoxelBuffer::setVoxelType(int iXPos, int iYPos, int iZPos, int iVoxelType) {
	int iVoxelOffset = iXPos + iYPos * 64 + iZPos * 4096;
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


