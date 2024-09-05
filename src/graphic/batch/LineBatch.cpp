#include "LineBatch.h"

void LineBatch::build(GLenum usage, bool f_clear_data)
{
	for (size_t i = 0; i < meshes.size(); i++) {
		const auto& vertices = meshes[i]->getVertices();
		const auto& indices = meshes[i]->getIndices();

		glm::ivec3 relative_position = objects[i]->getPosition() - position;
		glm::vec3 relative_offset = objects[i]->getOffset() - offset;

		for (const auto& vertex : vertices) {
			VertexPoint v = vertex;
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

void LineBatch::addMesh(const SimpleObject& object, const std::shared_ptr<Mesh<VertexPoint>>& mesh_ptr)
{
	std::shared_ptr<SimpleObject> object_ptr = std::make_shared<SimpleObject>(object.getPosition(), object.getOffset());
	objects.push_back(object_ptr);

	meshes.push_back(mesh_ptr);
}

void LineBatch::addMesh(const SimpleObject& object, const Mesh<VertexPoint>& mesh)
{
	std::shared_ptr<SimpleObject> object_ptr = std::make_shared<SimpleObject>(object.getPosition(), object.getOffset());
	objects.push_back(object_ptr);

	std::shared_ptr<Mesh<VertexPoint>> mesh_ptr = std::make_shared<Mesh<VertexPoint>>(mesh.getVertices(), mesh.getIndices());
	meshes.push_back(mesh_ptr);
}

void LineBatch::setLineWidth(float width)
{
	line_width = width;
}