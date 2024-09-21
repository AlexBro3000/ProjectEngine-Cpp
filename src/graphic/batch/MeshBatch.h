#pragma once
#include <memory>

#include "../../graphic/batch/Batch.h"
#include "../../graphic/mesh/Mesh.h"
#include "../../graphic/mesh/Vertex.h"
#include "../../object/Object.h"

class MeshBatch : public ObjSPs, public Batch<VertexMesh> {
private:
	std::vector<ObjSPs> objects;
	std::vector<std::shared_ptr<Mesh<VertexMesh>>> meshes;

public:
	MeshBatch(const glm::ivec3& position) : ObjSPs(position), Batch() {}
	~MeshBatch() = default;

	void build(GLenum usage, bool f_clear_data = true) override;
	void render() const;

	void clear() override;

    void addMesh(const ObjSPs& object, const std::shared_ptr<Mesh<VertexMesh>>& mesh_ptr);
    void addMesh(const ObjSPs& object, const Mesh<VertexMesh>& mesh);

private:
    MeshBatch(const MeshBatch&) = delete;
    MeshBatch(MeshBatch&&) = delete;

    MeshBatch& operator=(const MeshBatch&) = delete;
    MeshBatch& operator=(MeshBatch&&) = delete;
};