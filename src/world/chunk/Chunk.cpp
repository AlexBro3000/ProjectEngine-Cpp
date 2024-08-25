#include "Chunk.h"
#include "../../graphic/mesh/Mesh.h"
#include "../../world/voxel/Voxel.hpp"

#define IS_IN(X,Y,Z) ((X) >= 0 && (X) < CHUNK_SIZE_X && (Y) >= 0 && (Y) < CHUNK_SIZE_Y && (Z) >= 0 && (Z) < CHUNK_SIZE_Z)
#define VOXEL(X,Y,Z) (voxels[((Y) * CHUNK_SIZE_X + (X)) * CHUNK_SIZE_Z + (Z)])
#define IS_BLOCKED(X,Y,Z) ((IS_IN(X,Y,Z)) && VOXEL(X,Y,Z).id != 0)

Chunk::Chunk()
{
	voxels = new Voxel[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];

	for (int y = 0; y < CHUNK_SIZE_Y; y++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {
				// int id = y <= (sin(x * 0.3f) * 0.5f + 0.5f) * 10;

				int id = 0;

				if (y <= 6) {
					id = 3;
				}
				else if (y <= 9) {
					id = 2;
				}
				else if (y == 10) {
					id = 1;
				}

				voxels[(y * CHUNK_SIZE_X + x) * CHUNK_SIZE_Z + z].id = id;
			}
		}
	}
}

Chunk::~Chunk()
{
	delete voxels;
}

Mesh* Chunk::buildMesh()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	int index = 0;

	for (int y = 0; y < CHUNK_SIZE_Y; y++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {
				unsigned int id = voxels[(y * CHUNK_SIZE_X + x) * CHUNK_SIZE_Z + z].id;

				if (id == 0) {
					continue;
				}

				// X //

				if (!IS_BLOCKED(x + 1, y, z)) {
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z - 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}
				if (!IS_BLOCKED(x - 1, y, z)) {
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}

				// Y //

				if (!IS_BLOCKED(x, y + 1, z)) {
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}
				if (!IS_BLOCKED(x, y - 1, z)) {
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}

				// Z //

				if (!IS_BLOCKED(x, y, z + 1)) {
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z + 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z + 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z + 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z + 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}
				if (!IS_BLOCKED(x, y, z - 1)) {
					vertices.push_back(Vertex({ x + 0.5f, y - 0.5f, z - 0.5f }, { 0.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y - 0.5f, z - 0.5f }, { 1.0f, 0.0f }, id - 1));
					vertices.push_back(Vertex({ x - 0.5f, y + 0.5f, z - 0.5f }, { 1.0f, 1.0f }, id - 1));
					vertices.push_back(Vertex({ x + 0.5f, y + 0.5f, z - 0.5f }, { 0.0f, 1.0f }, id - 1));

					std::vector<int> values = { index + 0, index + 1, index + 2, index + 0, index + 2, index + 3 };
					indices.insert(indices.end(), values.begin(), values.end());

					index += 4;
				}
			}
		}
	}

	Mesh* mesh = new Mesh();
	mesh->build(vertices, indices, GL_STATIC_DRAW);
	return mesh;
}