


//#pragma once
//
//class Chunk
//{
//public:
//	Chunk();
//	~Chunk();
//
//private:
//
//};

//
//#include "../../../config/type/TypeDef_Int.hpp"
//#include "../../../config/type/TypeDef_Ver.hpp"
//
//class Voxel;
//class Mesh;
//
//struct RenderData
//{
//	float* vertices;
//	size_t size;
//};
//
//class Chunk
//{
//private:
//	Voxel*     voxels;        // Массив вокселей
//	RenderData render_data;
//
//	vec3_i32   position;      // Позиция чанка
//	_uint32_t  volume;        // Объем чанка
//
//	bool       f_processing;
//	bool       f_load;
//	bool       f_build;
//	bool       f_build_mesh;
//
//	friend class ChunkController;
//	friend class ChunkLoader;
//	friend class Chunks;
//	friend class WorldGenerator;
//
//
//public:
//	Chunk(vec3_i32 position);
//	~Chunk();
//
//	vec3_i32  getPosition();
//	Voxel*    getVoxel(vec3_ui8 pos);
//	// _uint32_t getVolume();
//
//	bool      isBuildMesh();
//
//	Mesh*     buildMesh(Mesh* mesh, bool threading);
//
//};
//
