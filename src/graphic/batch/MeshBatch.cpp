#include "MeshBatch.h"

void MeshBatch::build(GLenum usage, bool f_clear_data)
{
	size_t index_offset = 0;

	for (size_t i = 0; i < meshes.size(); i++) {
		glm::ivec3 position = objects[i].getPosition() - ObjSPs::position;

		const auto& vertices = meshes[i]->getVertices();
		const auto& indices = meshes[i]->getIndices();


		for (const auto& vertex : vertices) {
			VertexMesh v = vertex;
			v.position += glm::vec3(position);
			Batch::vertices.push_back(v);
		}

		for (const auto& index : indices) {
			Batch::indices.push_back(index_offset + index);
		}

		index_offset += vertices.size();
	}

	Batch::build(usage, f_clear_data);

	if (f_clear_data) {
		MeshBatch::clear();
	}
}

void MeshBatch::render() const
{
	Batch::render(GL_TRIANGLES);
}

void MeshBatch::clear()
{
	Batch::clear();
	objects.clear();
	meshes.clear();
}

void MeshBatch::addMesh(const ObjSPs& object, const std::shared_ptr<Mesh<VertexMesh>>& mesh_ptr)
{
	objects.push_back(object);
	meshes.push_back(mesh_ptr);
}

void MeshBatch::addMesh(const ObjSPs& object, const Mesh<VertexMesh>& mesh)
{
	std::shared_ptr<Mesh<VertexMesh>> mesh_ptr = std::make_shared<Mesh<VertexMesh>>(mesh.getVertices(), mesh.getIndices());
	MeshBatch::addMesh(object, mesh_ptr);
}