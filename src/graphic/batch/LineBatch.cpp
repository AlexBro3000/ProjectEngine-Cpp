#include "LineBatch.h"

void LineBatch::build(GLenum usage, bool f_clear_data)
{
	size_t index_offset = 0;

	for (size_t i = 0; i < meshes.size(); i++) {
		glm::ivec3 position = objects[i].getPosition() - ObjSPs::position;

		const auto& vertices = meshes[i]->getVertices();
		const auto& indices = meshes[i]->getIndices();

		for (const auto& vertex : vertices) {
			VertexPoint v = vertex;
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
		LineBatch::clear();
	}
}

void LineBatch::render() const
{
	glLineWidth(line_width);
	Batch::render(GL_LINES);
}

void LineBatch::clear()
{
	Batch::clear();
	objects.clear();
	meshes.clear();
}

void LineBatch::addMesh(const ObjSPs& object, const std::shared_ptr<Mesh<VertexPoint>>& mesh_ptr)
{
	objects.push_back(object);
	meshes.push_back(mesh_ptr);
}

void LineBatch::addMesh(const ObjSPs& object, const Mesh<VertexPoint>& mesh)
{
	std::shared_ptr<Mesh<VertexPoint>> mesh_ptr = std::make_shared<Mesh<VertexPoint>>(mesh.getVertices(), mesh.getIndices());
	LineBatch::addMesh(object, mesh_ptr);
}

void LineBatch::setLineWidth(float width)
{
	line_width = width;
}