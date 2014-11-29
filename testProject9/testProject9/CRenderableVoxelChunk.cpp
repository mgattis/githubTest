#include <glm/gtc/noise.hpp>
#include "CRenderableVoxelChunk.hpp"

typedef struct _ATTRIB_ARRAY {
	GLfloat xv, yv, zv;
	GLfloat xn, yn, zn;
}ATTRIB_ARRAY;

void addVertex(ATTRIB_ARRAY *currentAttrib, GLfloat xv, GLfloat yv, GLfloat zv) {
	currentAttrib->xv = xv;
	currentAttrib->yv = yv;
	currentAttrib->zv = zv;
}

void addNormal(ATTRIB_ARRAY *currentAttrib, GLfloat xn, GLfloat yn, GLfloat zn) {
	currentAttrib->xn = xn;
	currentAttrib->yn = yn;
	currentAttrib->zn = zn;
}

CRenderableVoxelChunk::CRenderableVoxelChunk() {
	map = NULL;

	glBuffers[0] = NULL;
	glBuffers[1] = NULL;

	iEditCount = 0;
	iVoxelCount = 0;

	chunkLocation.iX = 0;
	chunkLocation.iY = 0;
	chunkLocation.iZ = 0;

	initialize();
}

CRenderableVoxelChunk::CRenderableVoxelChunk(int iX, int iY, int iZ, IVoxelMap *map) {
	this->map = map;

	glBuffers[0] = NULL;
	glBuffers[1] = NULL;

	iEditCount = 0;
	iVoxelCount = 0;

	chunkLocation.iX = iX;
	chunkLocation.iY = iY;
	chunkLocation.iZ = iZ;

	initialize();
}

void CRenderableVoxelChunk::initialize() {
	for (int i = 0; i < CHUNK_XSIZE; i++) {
		for (int j = 0; j < CHUNK_YSIZE; j++) {
			glm::vec2 position(i, j);
			position -= glm::vec2(CHUNK_XSIZE / 2.0, CHUNK_YSIZE / 2.0);
			position /= glm::vec2(CHUNK_XSIZE / 2.0, CHUNK_YSIZE / 2.0);

			float value = glm::simplex(position)/2.0+0.5;
			value *= CHUNK_ZSIZE;
			value = value / 4.0 + 16.0;

			for (int k = 0; k < CHUNK_ZSIZE; k++) {
				if (k <= value) {
					setVoxel(i, j, k, 1);
				}
				else {
					setVoxel(i, j, k, 0);
				}
			}
		}
	}
}

unsigned char CRenderableVoxelChunk::getWorldVoxel(int iX, int iY, int iZ) {
	int iChunkX = iX / CHUNK_XSIZE;
	int iChunkY = iY / CHUNK_YSIZE;
	int iChunkZ = iZ / CHUNK_ZSIZE;

	iChunkX = iX < 0 ? iChunkX - 1 : iChunkX;
	iChunkY = iY < 0 ? iChunkY - 1 : iChunkY;
	iChunkZ = iZ < 0 ? iChunkZ - 1 : iChunkZ;

	if (iChunkX == chunkLocation.iX && iChunkY == chunkLocation.iY && iChunkZ == chunkLocation.iZ) {
		return getVoxel(iX % CHUNK_XSIZE, iY % CHUNK_YSIZE, iZ % CHUNK_ZSIZE);
	}
	else if (map) {
		CVoxelChunk *voxelChunk = map->getChunk(iChunkX, iChunkY, iChunkZ);
		if (voxelChunk) {
			return voxelChunk->getVoxel(iX % CHUNK_XSIZE, iY % CHUNK_YSIZE, iZ % CHUNK_ZSIZE);
		}
	}
	return 0;
}

CGLBuffer *CRenderableVoxelChunk::getDrawGLBuffer() {
	return glBuffers[!iRenderBuffer];
}

CGLBuffer *CRenderableVoxelChunk::getBuildGLBuffer() {
	CGLBuffer *glBuffer = glBuffers[iRenderBuffer];

	if (glBuffer) {
		return glBuffer;
	}
	else {
		glBuffer = new CGLBuffer();
		glBuffers[iRenderBuffer] = glBuffer;
		glBuffer->setShader(CGLShaderManager::instance()->get("shader_voxelterrain"));
		glBuffer->setDrawMode(GL_QUADS);
		return glBuffer;
	}
}

void CRenderableVoxelChunk::checkForBuild() {
	if (iVoxelCount && iEditCount) {
		build();
	}
}

void CRenderableVoxelChunk::build() {
	ATTRIB_ARRAY currentAttrib;

	std::vector<ATTRIB_ARRAY> attribArray;
	std::vector<GLuint> indexArray;
	int iCount = 0;

	iEditCount = 0;

	CGLBuffer *glBuffer = getBuildGLBuffer();

	for (int i = 0; i < CHUNK_XSIZE; i++) {
		for (int j = 0; j < CHUNK_YSIZE; j++) {
			for (int k = 0; k < CHUNK_ZSIZE; k++) {
				int iWorldX = chunkLocation.iX * CHUNK_XSIZE + i;
				int iWorldY = chunkLocation.iY * CHUNK_YSIZE + j;
				int iWorldZ = chunkLocation.iZ * CHUNK_ZSIZE + k;
				if (getWorldVoxel(iWorldX, iWorldY, iWorldZ)) {
					if (!getWorldVoxel(iWorldX - 1, iWorldY, iWorldZ)) {
						addVertex(&currentAttrib, i, j, k);
						addNormal(&currentAttrib, -1.0, 0.0, 0.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j + 1.0, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
					if (!getWorldVoxel(iWorldX + 1, iWorldY, iWorldZ)) {
						addVertex(&currentAttrib, i + 1.0, j, k);
						addNormal(&currentAttrib, 1.0, 0.0, 0.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
					if (!getWorldVoxel(iWorldX, iWorldY - 1, iWorldZ)) {
						addVertex(&currentAttrib, i, j, k);
						addNormal(&currentAttrib, 0.0, -1.0, 0.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
					if (!getWorldVoxel(iWorldX, iWorldY + 1, iWorldZ)) {
						addVertex(&currentAttrib, i, j + 1.0, k);
						addNormal(&currentAttrib, 0.0, 1.0, 0.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
					if (!getWorldVoxel(iWorldX, iWorldY, iWorldZ - 1)) {
						addVertex(&currentAttrib, i, j, k);
						addNormal(&currentAttrib, 0.0, 0.0, -1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j + 1.0, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j, k);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
					if (!getWorldVoxel(iWorldX, iWorldY, iWorldZ + 1)) {
						addVertex(&currentAttrib, i, j, k + 1.0);
						addNormal(&currentAttrib, 0.0, 0.0, 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i + 1.0, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
						addVertex(&currentAttrib, i, j + 1.0, k + 1.0);
						attribArray.push_back(currentAttrib); indexArray.push_back(iCount++);
					}
				}
			}
		}
	}

	glBuffer->setVertexData((GLfloat *)attribArray.data(), iCount*6);
	glBuffer->setIndexData((GLuint *)indexArray.data(), iCount);
	glBuffer->setAttribute("vertex3f", 3, 6, 0);
	glBuffer->setAttribute("normal3f", 3, 6, 3);
	iRenderBuffer = !iRenderBuffer;
	glBuffer = getBuildGLBuffer();
	if (glBuffer) {
		glBuffer->clear();
	}
}

void CRenderableVoxelChunk::update() {
	checkForBuild();
}

void CRenderableVoxelChunk::draw() {
	CGLBuffer *glBuffer = getDrawGLBuffer();

	if (glBuffer) {
		glPushMatrix();
		//glTranslatef(chunkLocation.iX*CHUNK_XSIZE, chunkLocation.iY*CHUNK_YSIZE, chunkLocation.iZ*CHUNK_ZSIZE);
		glBuffer->drawElements();
		glPopMatrix();
	}
}