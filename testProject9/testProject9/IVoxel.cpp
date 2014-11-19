#include "IVoxel.hpp"

IVoxel::IVoxel() {
	iType = 0;

	iXPos = 0;
	iYPos = 0;
	iZPos = 0;

	voxelBuffer = NULL;
}

IVoxel::IVoxel(int iXPos, int iYPos, int iZPos) {
	iType = 0;
	
	this->iXPos = iXPos;
	this->iYPos = iYPos;
	this->iZPos = iZPos;

	voxelBuffer = NULL;
}

IVoxel::IVoxel(int iXPos, int iYPos, int iZPos, IVoxelBuffer *voxelBuffer) {
	iType = 0;

	this->iXPos = iXPos;
	this->iYPos = iYPos;
	this->iZPos = iZPos;

	this->voxelBuffer = voxelBuffer;
	this->iType = voxelBuffer->getVoxelType(iXPos, iYPos, iZPos);
}

void IVoxel::setType(int iType) {
	this->iType = iType;

	if (voxelBuffer) {
		voxelBuffer->setVoxelType(iXPos, iYPos, iZPos, iType);
	}
}

void IVoxel::setCoordinates(int iXPos, int iYPos, int iZPos) {
	this->iXPos;
	this->iYPos;
	this->iZPos;

	if (voxelBuffer) {
		voxelBuffer->getVoxelType(iXPos, iYPos, iZPos);
	}
}

void IVoxel::attachToBuffer(IVoxelBuffer *voxelBuffer) {
	this->voxelBuffer = voxelBuffer;
	this->iType = voxelBuffer->getVoxelType(iXPos, iYPos, iZPos);
}
