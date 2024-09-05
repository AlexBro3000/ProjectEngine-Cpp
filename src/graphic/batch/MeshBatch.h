#pragma once
#include <memory>

#include "../../graphic/batch/Batch.h"
#include "../../graphic/mesh/Mesh.h"
#include "../../graphic/mesh/Vertex.h"
#include "../../object/SimpleObject.h"

class MeshBatch : public SimpleObject, public Batch<VertexMesh> {
private:
	std::vector<std::shared_ptr<SimpleObject>> objects;
	std::vector<std::shared_ptr<Mesh<VertexMesh>>> meshes;

public:
	MeshBatch(const glm::ivec3& position, const glm::vec3& offset) : SimpleObject(position, offset), Batch() {}
	~MeshBatch() = default;

	void build(GLenum usage, bool f_clear_data = true) override;
	void render() const;

	void clear() override;

    void addMesh(const SimpleObject& object, const std::shared_ptr<Mesh<VertexMesh>>& mesh_ptr);
    void addMesh(const SimpleObject& object, const Mesh<VertexMesh>& mesh);

private:
    MeshBatch(const MeshBatch&) = delete;
    MeshBatch(MeshBatch&&) = delete;

    MeshBatch& operator=(const MeshBatch&) = delete;
    MeshBatch& operator=(MeshBatch&&) = delete;
};