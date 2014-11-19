#ifndef _IVOXEL_HPP
#define _IVOXEL_HPP
#include "IVoxelBuffer.hpp"
#include "main.hpp"

class IVoxel {
private:
	int iType;
	int iXPos;
	int iYPos;
	int iZPos;

	IVoxelBuffer *voxelBuffer;

public:
	IVoxel();
	IVoxel(int iXPos, int iYPos, int iZPos);
	IVoxel(int iXPos, int iYPos, int iZPos, IVoxelBuffer *voxelBuffer);

	int getXPos() { return iXPos; }
	int getYPos() { return iYPos; }
	int getZPos() { return iZPos; }

	void setType(int iType);
	int getType() { return iType; }

	void setCoordinates(int iXPos, int iYPos, int iZPos);
	void attachToBuffer(IVoxelBuffer *voxelBuffer);
};

#endif /* !_IVOXEL_HPP */