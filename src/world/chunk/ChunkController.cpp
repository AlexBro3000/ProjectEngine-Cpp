#include "ChunkController.h"
#include "../../world/chunk/Chunk.h"

ChunkController::ChunkController(const glm::ivec3& position) :
	SimpleObject(position, glm::ivec3(0.0f))
{
	chunks = new Chunk * [CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z];

	glm::ivec3 chunk_offset(
		CHUNK_SIZE_X * (CHUNK_COUNT_X / 2.0f - 0.5f),
		CHUNK_SIZE_Y * (CHUNK_COUNT_Y / 2.0f - 0.5f),
		CHUNK_SIZE_Z * (CHUNK_COUNT_Z / 2.0f - 0.5f)
	);

	auto adjustPosition = [](int position, int chunk_size) -> int {
		return chunk_size * static_cast<int>(std::round(static_cast<float>(position) / chunk_size));
		};


	for (int y = 0; y < CHUNK_COUNT_Y; y++) {
		for (int x = 0; x < CHUNK_COUNT_X; x++) {
			for (int z = 0; z < CHUNK_COUNT_Z; z++) {
				glm::ivec3 chunk_position = glm::ivec3(x, y, z) * glm::ivec3(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);
				chunk_position -= chunk_offset;

				chunk_position.x += adjustPosition(position.x, CHUNK_SIZE_X);
				chunk_position.y += adjustPosition(position.y, CHUNK_SIZE_Y);
				chunk_position.z += adjustPosition(position.z, CHUNK_SIZE_Z);

				chunks[(y * CHUNK_COUNT_X + x) * CHUNK_COUNT_Z + z] = new Chunk(chunk_position);
			}
		}
	}
}

ChunkController::~ChunkController()
{
	for (size_t i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z; i++) {
		delete chunks[i];
	}
	delete[] chunks;
}

void ChunkController::build()
{
	for (size_t i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z; i++) {
		chunks[i]->build(this, i);
	}
}

Chunk** ChunkController::getChunks() const
{
	return chunks;
}
