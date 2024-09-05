#pragma once
#include <memory>

#include "../../graphic/batch/Batch.h"
#include "../../graphic/mesh/Mesh.h"
#include "../../graphic/mesh/Vertex.h"
#include "../../object/SimpleObject.h"

class LineBatch : public SimpleObject, public Batch<VertexPoint> {
private:
	std::vector<std::shared_ptr<SimpleObject>> objects;
	std::vector<std::shared_ptr<Mesh<VertexPoint>>> meshes;

	float line_width;

public:
	LineBatch(const glm::ivec3& position, const glm::vec3& offset, float width = 1.0f) : SimpleObject(position, offset), Batch(), line_width(width) {}
	~LineBatch() = default;

	void build(GLenum usage, bool f_clear_data = true) override;
	void render() const;

	void clear() override;

	void addMesh(const SimpleObject& object, const std::shared_ptr<Mesh<VertexPoint>>& mesh_ptr);
	void addMesh(const SimpleObject& object, const Mesh<VertexPoint>& mesh);

	void setLineWidth(float width);

private:
	LineBatch(const LineBatch&) = delete;
	LineBatch(LineBatch&&) = delete;

	LineBatch& operator=(const LineBatch&) = delete;
	LineBatch& operator=(LineBatch&&) = delete;
};