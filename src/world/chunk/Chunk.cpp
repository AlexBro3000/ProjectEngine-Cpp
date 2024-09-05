#include "Chunk.h"

#include "../../world/chunk/ChunkController.h"
#include "../../world/voxel/Voxel.hpp"

Chunk::Chunk(const glm::ivec3& position) :
	SimpleObject(position, glm::vec3(0.0f))
{
	voxels = new Voxel[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
	mesh = std::make_shared<Mesh<VertexMesh>>();

	glm::ivec3 voxel_offset(CHUNK_SIZE_X / 2, CHUNK_SIZE_Y / 2, CHUNK_SIZE_Z / 2);

	for (int y = 0; y < CHUNK_SIZE_Y; y++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {


				glm::ivec3 voxel_position = glm::ivec3(x, y, z) + position;
				voxel_position -= voxel_offset;

				int id = voxel_position.y <= (sin(voxel_position.x * 0.15f) * 0.5f + 0.2f) * 10;

				if (voxel_position.y < 0)   id = 2;
				if (voxel_position.y < -10) id = 3;

				voxels[(y * CHUNK_SIZE_X + x) * CHUNK_SIZE_Z + z].id = id;
			}
		}
	}
}

Chunk::~Chunk()
{
	delete voxels;
}

void Chunk::build(ChunkController* chunk_controller, int index)
{
	std::vector<VertexMesh> vertices;
	std::vector<unsigned int> indices;
	int step = 0;

	for (int y = 0; y < CHUNK_SIZE_Y; y++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {
				unsigned int id = voxels[(y * CHUNK_SIZE_X + x) * CHUNK_SIZE_Z + z].id;

				if (id == 0) {
					continue;
				}

				// X //

				if (!IS_BLOCKED(glm::ivec3(x + 1, y, z), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z - 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}
				if (!IS_BLOCKED(glm::ivec3(x - 1, y, z), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}

				// Y //

				if (!IS_BLOCKED(glm::ivec3(x, y + 1, z), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}
				if (!IS_BLOCKED(glm::ivec3(x, y - 1, z), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}

				// Z //

				if (!IS_BLOCKED(glm::ivec3(x, y, z + 1), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}
				if (!IS_BLOCKED(glm::ivec3(x, y, z - 1), index, chunk_controller)) {
					vertices.push_back(VertexMesh({ x + 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(VertexMesh({ x - 0.5f, y + 0.5f, z - 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(VertexMesh({ x + 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { step + 0, step + 1, step + 2, step + 0, step + 2, step + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					step += 4;
				}
			}
		}
	}

	mesh->setData(vertices, indices);
	mesh->build(GL_STATIC_DRAW);
}

std::shared_ptr<Mesh<VertexMesh>> Chunk::getMesh() const
{
	return mesh;
}

bool Chunk::IS_BLOCKED(glm::ivec3 pos, int index, ChunkController* chunk_controller)
{
	auto isInBounds = [](int value, int max) {
		return value >= 0 && value < max;
		};

	if (isInBounds(pos.x, CHUNK_SIZE_X) && isInBounds(pos.y, CHUNK_SIZE_Y) && isInBounds(pos.z, CHUNK_SIZE_Z)) {
		return voxels[(pos.y * CHUNK_SIZE_X + pos.x) * CHUNK_SIZE_Z + pos.z].id != 0;
	}

	int x = (index / CHUNK_COUNT_Z) % CHUNK_COUNT_X;
	int y = index / (CHUNK_COUNT_Z * CHUNK_COUNT_X);
	int z = index % CHUNK_COUNT_Z;

	auto adjustPosition = [&](int& pos, int& coord, int size, int maxCoord) {
		while (pos < 0) {
			pos += size;
			coord--;
		}
		while (pos >= size) {
			pos -= size;
			coord++;
		}
		return isInBounds(coord, maxCoord);
		};

	bool isValidX = adjustPosition(pos.x, x, CHUNK_SIZE_X, CHUNK_COUNT_X);
	bool isValidY = adjustPosition(pos.y, y, CHUNK_SIZE_Y, CHUNK_COUNT_Y);
	bool isValidZ = adjustPosition(pos.z, z, CHUNK_SIZE_Z, CHUNK_COUNT_Z);

	if (isValidX && isValidY && isValidZ) {
		Voxel voxel = chunk_controller->getChunks()[(y * CHUNK_COUNT_X + x) * CHUNK_COUNT_Z + z]
			->voxels[(pos.y * CHUNK_SIZE_X + pos.x) * CHUNK_SIZE_Z + pos.z];
		return voxel.id != 0;
	}

	return false;
}