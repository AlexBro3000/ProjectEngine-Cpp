#pragma once
#include "../../graphic/mesh/Mesh.h"
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <vector>

//struct VertexPoint;
//class Mesh;

class LineBatch
{
private:
    std::vector<VertexPoint*> vertices;
    std::vector<unsigned int> indices;
    unsigned int index = 0;

    Mesh mesh;
    GLenum usage;
    float line_width;


public:
    LineBatch(GLenum usage = GL_DYNAMIC_DRAW);
    ~LineBatch();

    void build();
    void render() const;

    void addLine(const VertexPoint& vertex_1, const VertexPoint& vertex_2);
    void setLineWidth(float width);

    void clear();

private:

};




//class LineBatch {
//	Mesh* mesh;
//	float* buffer;
//	size_t index;
//	size_t capacity;
//public:
//	LineBatch(size_t capacity);
//	~LineBatch();
//
//	void line(float x1, float y1, float z1, float x2, float y2, float z2,
//		float r, float g, float b, float a);
//	void box(float x, float y, float z, float w, float h, float d,
//		float r, float g, float b, float a);
//
//	void render();
//};
