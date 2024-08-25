#include "Chunk.h"


//
//#include <math.h>
//#include "../voxel/Voxel.h"
//#include "../../../config/define/Define_Chunk.h"
//#include "../../../graphic/mesh/Mesh.h"
//
//
//Chunk::Chunk(vec3_i32 position)
//{
//	this->position       = position;
//	this->volume         = pow(CHUNK_SIZE, 3);
//	voxels               = new Voxel[volume];
//	render_data.vertices = nullptr;
//	render_data.size     = 0;
//
//	f_load               = false;
//	f_build              = false;
//	f_build_mesh         = false;
//	f_processing         = true;
//}
//
//Chunk::~Chunk()
//{
//	if (render_data.size) {
//		delete render_data.vertices;
//	}
//	delete[] voxels;
//}
//
//vec3_i32 Chunk::getPosition()
//{
//	return position;
//}
//
//Voxel* Chunk::getVoxel(vec3_ui8 pos)
//{
//	return &voxels[GET_VOXEL_INDEX(pos.x, pos.y, pos.z, CHUNK_SIZE)];
//}
//
////_uint32_t Chunk::getVolume()
////{
////	return volume;
////}
//
//bool Chunk::isBuildMesh()
//{
//	if (f_processing || !f_load || !f_build || !f_build_mesh)
//		return false;
//	return true;
//}
//
//Mesh* Chunk::buildMesh(Mesh* mesh, bool threading)
//{
//	mesh->build(render_data.vertices, render_data.size / VERTEX_ATTRS_SIZE, vertex_attrs, GL_DYNAMIC_DRAW);
//
//	if (render_data.size) {
//		delete render_data.vertices;
//
//		render_data.vertices = nullptr;
//		render_data.size     = 0;
//	}
//	if (!threading) {
//		f_build_mesh = true;
//	}
//	return mesh;
//}