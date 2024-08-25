#pragma once
#include "../../object/SimpleObject.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

class Voxel;
class Mesh;

class Chunk // : public SimpleObject
{
private:
	Voxel* voxels;

public:
	Chunk();
	~Chunk();

	Mesh* buildMesh();

private:

};