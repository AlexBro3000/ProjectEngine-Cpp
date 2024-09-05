#pragma once
#include "../../object/SimpleObject.h"

#define CHUNK_COUNT_X 6
#define CHUNK_COUNT_Y 4
#define CHUNK_COUNT_Z 6

class Chunk;

class ChunkController : public SimpleObject {
private:
	Chunk** chunks;

	friend class Chunk;

public:
	ChunkController(const glm::ivec3& position);
	~ChunkController();

	void build();

	Chunk** getChunks() const;

private:
};