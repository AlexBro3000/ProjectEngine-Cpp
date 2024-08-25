//#pragma once
//#include <vector>
//#include "../../../config/type/TypeDef_Int.hpp"
//#include "../../../config/type/TypeDef_Ver.hpp"
//
//class Chunk;
//class Voxel;
//class Mesh;
//
//class Chunks
//{
//private:
//	Chunk**             chunks;        // Массив чанков
//	Mesh**              meshes;        // Массив мешей
//
//	vec2_ui8            border;
//	_uint32_t           volume;
//	vec3_i32            offset;
//
//	std::vector<Chunk*> chunk_stack;
//	std::vector<Mesh*>  mesh_stack;
//	_uint8_t*           grid_lod;
//
//	bool                f_processing;
//	bool                f_modified;
//
//	friend class ChunkController;
//	friend class ChunkLoader;
//
//public:
//	Chunks(vec2_ui8 border, vec3_i32 offset);
//	~Chunks();
//
//	Chunk*    getChunk(_uint32_t index);
//	Mesh*     getMesh(_uint32_t index);
//	Mesh*     getFreeMesh();
//	_uint32_t getVolume();
//	vec3_i32  getOffset();
//
//	void      setOffset(vec3_i32 pos);
//
//	void      clearStack();
//
//private:
//	void      addToStack(Chunk* chunk, Mesh* mesh);
//	void      translation(vec3_i32 shift);
//
//};
//
