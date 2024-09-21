#include "ChunkController.h"

#include "../../world/chunk/Chunk.h"
#include "../../world/voxel/Voxel.hpp"

ChunkController::ChunkController(const glm::ivec3& position) :
    ObjSPs(ChunkController::adjustPosition(position))
{
    glm::ivec3 pos_offset;
    pos_offset.x = ObjSPs::position.x - (CHUNK_COUNT_X - 1) * CHUNK_SIZE_X / 2;
    pos_offset.y = ObjSPs::position.y - (CHUNK_COUNT_Y - 1) * CHUNK_SIZE_Y / 2;
    pos_offset.z = ObjSPs::position.z - (CHUNK_COUNT_Z - 1) * CHUNK_SIZE_Z / 2;

    chunks = new Chunk * [CHUNK_COUNT_X * CHUNK_COUNT_Y * CHUNK_COUNT_Z];
    for (int y = 0; y < CHUNK_COUNT_Y; y++) {
        for (int x = 0; x < CHUNK_COUNT_X; x++) {
            for (int z = 0; z < CHUNK_COUNT_Z; z++) {
                glm::ivec3 pos = glm::ivec3(CHUNK_SIZE_X * x, CHUNK_SIZE_Y * y, CHUNK_SIZE_Z * z) + pos_offset;

                size_t index = (y * CHUNK_COUNT_X + x) * CHUNK_COUNT_Z + z;
                chunks[index] = new Chunk(pos);
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
		if (!chunks[i]->f_modified) {
			continue;
		}

		chunks[i]->build(this, i);
		chunks[i]->f_modified = false;
	}
}

Chunk* ChunkController::getChunk(const glm::ivec3& position) const
{
    glm::ivec3 pos;
    pos.x = static_cast<int>(std::floor(static_cast<float>((position.x - ObjSPs::position.x) + CHUNK_COUNT_X * CHUNK_SIZE_X / 2) / CHUNK_SIZE_X));
    pos.y = static_cast<int>(std::floor(static_cast<float>((position.y - ObjSPs::position.y) + CHUNK_COUNT_Y * CHUNK_SIZE_Y / 2) / CHUNK_SIZE_Y));
    pos.z = static_cast<int>(std::floor(static_cast<float>((position.z - ObjSPs::position.z) + CHUNK_COUNT_Z * CHUNK_SIZE_Z / 2) / CHUNK_SIZE_Z));

    if (pos.x >= 0 && pos.x < CHUNK_COUNT_X && pos.y >= 0 && pos.y < CHUNK_COUNT_Y && pos.z >= 0 && pos.z < CHUNK_COUNT_Z) {
        size_t index = (pos.y * CHUNK_COUNT_X + pos.x) * CHUNK_COUNT_Z + pos.z;
        return chunks[index];
    }
    
    return nullptr;
}

Chunk** ChunkController::getChunks() const
{
    return chunks;
}

Voxel* ChunkController::getVoxel(const glm::ivec3& position) const
{
    Chunk* chunk = getChunk(position);

    if (chunk) {
        glm::ivec3 pos;
        pos.x = ((position.x - ObjSPs::position.x) + CHUNK_COUNT_X * CHUNK_SIZE_X / 2) % CHUNK_SIZE_X;
        pos.y = ((position.y - ObjSPs::position.y) + CHUNK_COUNT_Y * CHUNK_SIZE_Y / 2) % CHUNK_SIZE_Y;
        pos.z = ((position.z - ObjSPs::position.z) + CHUNK_COUNT_Z * CHUNK_SIZE_Z / 2) % CHUNK_SIZE_Z;

        if (pos.x >= 0 && pos.y >= 0 && pos.z >= 0) {
            return chunk->getVoxel(pos);
        }
    }

    return nullptr;
}

void ChunkController::setVoxel(const glm::ivec3& position, uint16_t id)
{
    Chunk* chunk = getChunk(position);

    if (chunk) {
        glm::ivec3 pos;
        pos.x = ((position.x - ObjSPs::position.x) + CHUNK_COUNT_X * CHUNK_SIZE_X / 2) % CHUNK_SIZE_X;
        pos.y = ((position.y - ObjSPs::position.y) + CHUNK_COUNT_Y * CHUNK_SIZE_Y / 2) % CHUNK_SIZE_Y;
        pos.z = ((position.z - ObjSPs::position.z) + CHUNK_COUNT_Z * CHUNK_SIZE_Z / 2) % CHUNK_SIZE_Z;

        if (pos.x >= 0 && pos.y >= 0 && pos.z >= 0) {
            chunk->setVoxel(pos, id);
            chunk->f_modified = true;

            if (pos.x == 0) {
                chunk = getChunk(position + glm::ivec3(-CHUNK_SIZE_X, 0, 0));
                if (chunk) chunk->f_modified = true;
            }
            else if (pos.x == CHUNK_SIZE_X - 1) {
                chunk = getChunk(position + glm::ivec3(CHUNK_SIZE_X, 0, 0));
                if (chunk) chunk->f_modified = true;
            }

            if (pos.y == 0) {
                chunk = getChunk(position + glm::ivec3(0, -CHUNK_SIZE_Y, 0));
                if (chunk) chunk->f_modified = true;
            }
            else if (pos.y == CHUNK_SIZE_Y - 1) {
                chunk = getChunk(position + glm::ivec3(0, CHUNK_SIZE_Y, 0));
                if (chunk) chunk->f_modified = true;
            }

            if (pos.z == 0) {
                chunk = getChunk(position + glm::ivec3(0, 0, -CHUNK_SIZE_Z));
                if (chunk) chunk->f_modified = true;
            }
            else if (pos.z == CHUNK_SIZE_Z - 1) {
                chunk = getChunk(position + glm::ivec3(0, 0, CHUNK_SIZE_Z));
                if (chunk) chunk->f_modified = true;
            }
        }
    }
}

Voxel* ChunkController::rayCast(
    const glm::ivec3& position, const glm::vec3& offset, const glm::vec3 direction,
    float max_length, glm::ivec3& ray_iend, glm::vec3& ray_end, glm::vec3& norm
)
{
    glm::ivec3 pos = position;
    glm::ivec3 ray_step = glm::sign(direction);

    // t_delta - Дистанция между границами вокселей по каждой оси
    // t_max   - Дистанция до ближайшей границы вокселя по каждой оси
    glm::vec3 t_delta, t_max;

    // Вычисляем t_delta и t_max для каждой оси
    for (int i = 0; i < 3; i++) {
        if (direction[i] != 0.0f) {
            float voxel_boundary = (ray_step[i] > 0 ? 1.0f - offset[i] : -offset[i]);
            t_delta[i] = glm::abs(1.0f / direction[i]);
            t_max[i] = voxel_boundary / direction[i];
        }
        else {
            t_delta[i] = std::numeric_limits<float>::infinity();
            t_max[i] = std::numeric_limits<float>::infinity();
        }
    }

    float ray_length = 0.0f;
    int index = -1;

    // Основной цикл DDA (Digital Differential Analyzer)
    while (ray_length < max_length) {
        Voxel* voxel = getVoxel(pos);

        if (voxel && voxel->id) {
            ray_iend = pos;

            ray_end = glm::fract(offset + ray_length * direction);
            norm = glm::vec3(0.0f);

            if (index == 0) {
                norm.x = -ray_step.x;
                ray_end.x = 0.5f + norm.x / 2;
            }
            if (index == 1) {
                norm.y = -ray_step.y;
                ray_end.y = 0.5f + norm.y / 2;
            }
            if (index == 2) {
                norm.z = -ray_step.z;
                ray_end.z = 0.5f + norm.z / 2;
            }

            return voxel;
        }

        if (t_max.x < t_max.y && t_max.x < t_max.z) {
            pos.x += ray_step.x;
            ray_length = t_max.x;
            t_max.x += t_delta.x;
            index = 0;
        }
        else if (t_max.y < t_max.z) {
            pos.y += ray_step.y;
            ray_length = t_max.y;
            t_max.y += t_delta.y;
            index = 1;
        }
        else {
            pos.z += ray_step.z;
            ray_length = t_max.z;
            t_max.z += t_delta.z;
            index = 2;
        }
    }

    return nullptr;
}

glm::ivec3 ChunkController::adjustPosition(const glm::ivec3& position)
{
    return glm::ivec3(
        static_cast<int>(std::round(static_cast<float>(position.x) / CHUNK_SIZE_X)) * CHUNK_SIZE_X,
        static_cast<int>(std::round(static_cast<float>(position.y) / CHUNK_SIZE_Y)) * CHUNK_SIZE_Y,
        static_cast<int>(std::round(static_cast<float>(position.z) / CHUNK_SIZE_Z)) * CHUNK_SIZE_Z
    );
}