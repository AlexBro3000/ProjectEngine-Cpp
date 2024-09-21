#pragma once
#include <memory>

#include "../../graphic/batch/Batch.h"
#include "../../graphic/mesh/Mesh.h"
#include "../../graphic/mesh/Vertex.h"
#include "../../object/Object.h"

class LineBatch : public ObjSPs, public Batch<VertexPoint> {
private:
	std::vector<ObjSPs> objects;
	std::vector<std::shared_ptr<Mesh<VertexPoint>>> meshes;

	float line_width;

public:
	LineBatch(const glm::ivec3& position, float width = 1.0f) : ObjSPs(position), Batch(), line_width(width) {}
	~LineBatch() = default;

	void build(GLenum usage, bool f_clear_data = true) override;
	void render() const;

	void clear() override;

	void addMesh(const ObjSPs& object, const std::shared_ptr<Mesh<VertexPoint>>& mesh_ptr);
	void addMesh(const ObjSPs& object, const Mesh<VertexPoint>& mesh);

	void setLineWidth(float width);

private:
	LineBatch(const LineBatch&) = delete;
	LineBatch(LineBatch&&) = delete;

	LineBatch& operator=(const LineBatch&) = delete;
	LineBatch& operator=(LineBatch&&) = delete;
};