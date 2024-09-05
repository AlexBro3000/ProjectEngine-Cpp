#include "MeshBatch.h"

void MeshBatch::build(GLenum usage, bool f_clear_data)
{
	for (size_t i = 0; i < meshes.size(); i++) {
		const auto& vertices = meshes[i]->getVertices();
		const auto& indices = meshes[i]->getIndices();

		glm::ivec3 relative_position = objects[i]->getPosition() - position;
		glm::vec3 relative_offset = objects[i]->getOffset() - offset;

		for (const auto& vertex : vertices) {
			VertexMesh v = vertex;
			v.position += glm::vec3(relative_position) + relative_offset;
			Batch::vertices.push_back(v);
		}

		for (const auto& index : indices) {
			Batch::indices.push_back(index + Batch::count);
		}

		Batch::count += vertices.size();
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

void MeshBatch::addMesh(const SimpleObject& object, const std::shared_ptr<Mesh<VertexMesh>>& mesh_ptr)
{
	std::shared_ptr<SimpleObject> object_ptr = std::make_shared<SimpleObject>(object.getPosition(), object.getOffset());
	objects.push_back(object_ptr);

	meshes.push_back(mesh_ptr);
}

void MeshBatch::addMesh(const SimpleObject& object, const Mesh<VertexMesh>& mesh)
{
	std::shared_ptr<SimpleObject> object_ptr = std::make_shared<SimpleObject>(object.getPosition(), object.getOffset());
	objects.push_back(object_ptr);

	std::shared_ptr<Mesh<VertexMesh>> mesh_ptr = std::make_shared<Mesh<VertexMesh>>(mesh.getVertices(), mesh.getIndices());
	meshes.push_back(mesh_ptr);
}