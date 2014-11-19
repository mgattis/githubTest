#include "CVoxelChunk.hpp"
#include <stdio.h>
#include <stdlib.h>

CVoxelChunk::CVoxelChunk() {
	this->iXPos = 0;
	this->iYPos = 0;
	this->iZPos = 0;

	voxelBuffer = new IVoxelBuffer();
	voxels = (IVoxel *)calloc(64 * 64 * 64, sizeof(IVoxel));

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			for (int k = 0; k < 64; k++) {
				int iVoxelOffset = i + j * 64 + k * 4096;
				voxels[iVoxelOffset] = IVoxel(i, j, k, voxelBuffer);
			}
		}
	}
}

CVoxelChunk::CVoxelChunk(int iXPos, int iYPos, int iZPos) {
	this->iXPos = iXPos;
	this->iYPos = iYPos;
	this->iZPos = iZPos;

	voxelBuffer = new IVoxelBuffer();
	voxels = (IVoxel *)calloc(64 * 64 * 64, sizeof(IVoxel));

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			for (int k = 0; k < 64; k++) {
				int iVoxelOffset = i + j * 64 + k * 4096;
				voxels[iVoxelOffset] = IVoxel(i, j, k, voxelBuffer);
			}
		}
	}
}

void CVoxelChunk::setCooridnates(int iXPos, int iYPos, int iZPos) {
	this->iXPos = iXPos;
	this->iYPos = iYPos;
	this->iZPos = iZPos;
}

IVoxel *CVoxelChunk::getVoxel(int iXPos, int iYPos, int iZPos) {
	return &voxels[iXPos + iYPos * 64 + iZPos * 4096];
}