#pragma once
#include "../../object/Object.h"

static size_t CHUNK_COUNT_X = 4;
static size_t CHUNK_COUNT_Y = 2;
static size_t CHUNK_COUNT_Z = 4;

class Chunk;
class Voxel;

class ChunkController : public ObjSPs {
private:
	Chunk** chunks;

	friend class Chunk;

public:
	ChunkController(const glm::ivec3& position);
	~ChunkController();

	void build();

	Chunk* getChunk(const glm::ivec3& position) const;
	Chunk** getChunks() const;
	Voxel* getVoxel(const glm::ivec3& position) const;

	void setVoxel(const glm::ivec3& position, uint16_t id);

	Voxel* rayCast(
		const glm::ivec3& position, const glm::vec3& offset, const glm::vec3 direction,
		float max_length, glm::ivec3& ray_iend, glm::vec3& ray_end, glm::vec3& norm
	);

private:
	static glm::ivec3 adjustPosition(const glm::ivec3& position);

};