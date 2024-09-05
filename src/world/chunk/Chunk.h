#pragma once
#include <memory>

#include "../../graphic/mesh/Mesh.h"
#include "../../object/SimpleObject.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

class ChunkController;
class Voxel;

class Chunk: public SimpleObject {
private:
	Voxel* voxels;
	std::shared_ptr<Mesh<VertexMesh>> mesh;

	friend class ChunkController;

public:
	Chunk(const glm::ivec3& position);
	~Chunk();

	void build(ChunkController* chunk_controller, int index);

	std::shared_ptr<Mesh<VertexMesh>> getMesh() const;

private:
	bool IS_BLOCKED(glm::ivec3 pos, int index, ChunkController* chunk_controller);

};