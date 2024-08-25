//#include "Chunks.h"
//
//#include "Chunk.h"
//#include "../../../config/define/Define_Chunk.h"
//#include "../../../graphic/mesh/Mesh.h"
//
//Chunks::Chunks(vec2_ui8 border, vec3_i32 offset)
//{
//	this->border = border;
//	this->volume = border.x * border.x * border.y;
//	this->offset = offset;
//
//	chunks   = new Chunk * [volume];
//	meshes   = new Mesh * [volume];
//	grid_lod = new _uint8_t[volume];
//	_uint32_t index = 0;
//	for (size_t y = 0; y < border.y; y++) {
//		for (size_t x = 0; x < border.x; x++) {
//			for (size_t z = 0; z < border.x; z++, index++) {
//				if (index >= volume) {
//					continue;
//				}
//				chunks[index] = nullptr;
//				meshes[index] = new Mesh();
//
//				vec3_i32 pos = vec3_i32(x - DISTANCE_RENDER.x, y - DISTANCE_RENDER.y, z - DISTANCE_RENDER.x);
//				if (getDistanceChunk_Lod(pos, DISTANCE_RENDER_LOD_0) <= 1.0f) {
//					grid_lod[index] = 0;
//					continue;
//				}
//				if (getDistanceChunk_Lod(pos, DISTANCE_RENDER_LOD_1) <= 1.0f) {
//					grid_lod[index] = 1;
//					continue;
//				}
//				if (getDistanceChunk_Lod(pos, DISTANCE_RENDER_LOD_2) <= 1.0f) {
//					grid_lod[index] = 2;
//					continue;
//				}
//				if (getDistanceChunk_Lod(pos, DISTANCE_RENDER_LOD_3) <= 1.0f) {
//					grid_lod[index] = 3;
//					continue;
//				}
//				if (getDistanceChunk_Lod(pos, DISTANCE_RENDER_LOD_4) <= 1.0f) {
//					grid_lod[index] = 4;
//					continue;
//				}
//				grid_lod[index] = 255;
//			}
//		}
//	}
//	f_processing = true;
//	f_modified = true;
//}
//
//Chunks::~Chunks()
//{
//	for (size_t i = 0; i < volume; i++) {
//		delete chunks[i];
//		delete meshes[i];
//	}
//	delete[] chunks;
//	delete[] meshes;
//	delete[] grid_lod;
//
//	for (Chunk* it : chunk_stack) {
//		while (it->f_processing) { }
//		delete it;
//	}
//	for (Mesh* it : mesh_stack)	{
//		delete it;
//	}
//}
//
//Chunk* Chunks::getChunk(_uint32_t index)
//{
//	return chunks[index];
//}
//
//Mesh* Chunks::getMesh(_uint32_t index)
//{
//	return meshes[index];
//}
//
//Mesh* Chunks::getFreeMesh()
//{
//	if (mesh_stack.size()) {
//		Mesh* mesh = mesh_stack[0];
//
//		mesh_stack.erase(mesh_stack.begin());
//		return mesh;
//	}
//	else {
//		return nullptr;
//	}
//}
//
//_uint32_t Chunks::getVolume()
//{
//	return volume;
//}
//
//vec3_i32 Chunks::getOffset()
//{
//	return offset;
//}
//
//void Chunks::setOffset(vec3_i32 pos)
//{
//	vec3_i32 offset_tmp = pos - offset;
//	offset_tmp /= CHUNK_SIZE;
//
//	if (offset_tmp.x != 0 || offset_tmp.y != 0 || offset_tmp.z != 0) {
//		f_processing = false;
//
//		translation(offset_tmp);
//		f_processing = true;
//		f_modified = true;
//	}
//	clearStack();
//}
//
//void Chunks::clearStack()
//{
//	std::vector<Chunk*> chunk_stack_tmp = chunk_stack;
//	chunk_stack.clear();
//
//	for (size_t i = 0; i < chunk_stack_tmp.size(); i++) {
//		Chunk* chunk = chunk_stack_tmp[i];
//
//		if (chunk->f_processing)
//			chunk_stack.push_back(chunk);
//		else
//			delete chunk;
//	}
//	chunk_stack_tmp.clear();
//}
//
//void Chunks::addToStack(Chunk* chunk, Mesh* mesh)
//{
//	if (chunk)
//		chunk_stack.push_back(chunk);
//	if (mesh)
//		mesh_stack.push_back(mesh);
//}
//
//void Chunks::translation(vec3_i32 shift)
//{
//	Chunk** chunks_shift = new Chunk * [volume];
//	Mesh** meshes_shift  = new Mesh * [volume];
//	for (size_t i = 0; i < volume; i++) {
//		chunks_shift[i] = nullptr;
//		meshes_shift[i] = nullptr;
//	}
//
//   	for (size_t y = 0; y < border.y; y++) {
//		for (size_t x = 0; x < border.x; x++) {
//			for (size_t z = 0; z < border.x; z++) {
//				_uint32_t index = GET_CHUNK_INDEX(x, y, z, border.x);
//
//				Chunk* chunk = chunks[index];
//				Mesh*  mesh  = meshes[index];
//
//				vec3_i32 pos_tmp = vec3_i32(x, y, z) - shift;
//				if (
//					pos_tmp.x < 0         || pos_tmp.y < 0         || pos_tmp.z < 0         || 
//					pos_tmp.x >= border.x || pos_tmp.y >= border.y || pos_tmp.z >= border.x
//					) {
//					addToStack(chunk, mesh);
//					continue;
//				}
//				else {
//					index = GET_CHUNK_INDEX(pos_tmp.x, pos_tmp.y, pos_tmp.z, border.x);
//
//					if (index < volume) {
//						chunks_shift[index] = chunk;
//						meshes_shift[index] = mesh;
//					}
//					else {
//						addToStack(chunk, mesh);
//					}
//				}
//
//			}
//		}
//	}
//	// Присваивание результатов
//	Chunk** chunks_tmp = chunks;
//	chunks             = chunks_shift;
//	Mesh**  meshes_tmp = meshes;
//	meshes             = meshes_shift;
//	f_modified = true;
//
//	// Сдвиг точки смещения
//	offset.x += shift.x * CHUNK_SIZE;
//	offset.y += shift.y * CHUNK_SIZE;
//	offset.z += shift.z * CHUNK_SIZE;
//
//	// Очищение памяти
//	delete chunks_tmp;
//	delete meshes_tmp;
//}
