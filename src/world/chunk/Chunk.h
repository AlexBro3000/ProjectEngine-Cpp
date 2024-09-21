#pragma once
#include <memory>

#include "../../graphic/mesh/Mesh.h"
#include "../../object/Object.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

class ChunkController;
class Voxel;

class Chunk : public ObjSPs {
private:
	Voxel* voxels;
	std::shared_ptr<Mesh<VertexMesh>> mesh;

	bool f_modified = true;

	friend class ChunkController;

public:
	Chunk(const glm::ivec3& position);
	~Chunk();

	void build(ChunkController* chunk_controller, int index);

	Voxel* getVoxel(const glm::ivec3& position) const;
	Voxel* getVoxels() const;
	std::shared_ptr<Mesh<VertexMesh>> getMesh() const;

	void setVoxel(const glm::ivec3& position, uint16_t id);

private:
	bool IS_BLOCKED(glm::ivec3 pos, int index, ChunkController* chunk_controller);

};