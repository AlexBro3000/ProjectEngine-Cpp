#include "LineBatch.h"

LineBatch::LineBatch(GLenum usage)
	: usage(usage), line_width(1.0f) {}

LineBatch::~LineBatch()
{
	LineBatch::clear();
}

void LineBatch::build()
{
	mesh.build(vertices, indices, usage);
	clear();
}

void LineBatch::render() const
{
    glLineWidth(line_width);
    mesh.render(GL_LINES);
}

void LineBatch::addLine(const VertexPoint& vertex_1, const VertexPoint& vertex_2)
{
    vertices.push_back(new VertexPoint(vertex_1));
    vertices.push_back(new VertexPoint(vertex_2));
    indices.push_back(index++);
    indices.push_back(index++);
}

void LineBatch::setLineWidth(float width)
{
    line_width = width;
}

void LineBatch::clear()
{
    for (VertexPoint* vertex : vertices) {
        delete vertex;
    }
    vertices.clear();
    indices.clear();
    index = 0;
}



//#include "LineBatch.h"
//#include "Mesh.h"
//
//#include <GL/glew.h>
//
//#define LB_VERTEX_SIZE (3+4)
//
//LineBatch::LineBatch(size_t capacity) : capacity(capacity) {
//	int attrs[] = { 3,4, 0 };
//	buffer = new float[capacity * LB_VERTEX_SIZE * 2];
//	mesh = new Mesh(buffer, 0, attrs);
//	index = 0;
//}
//
//LineBatch::~LineBatch() {
//	delete[] buffer;
//	delete mesh;
//}
//
//void LineBatch::line(float x1, float y1, float z1, float x2, float y2, float z2,
//	float r, float g, float b, float a) {
//	if (index >= capacity * LB_VERTEX_SIZE * 2)
//		return;
//	buffer[index] = x1;
//	buffer[index + 1] = y1;
//	buffer[index + 2] = z1;
//	buffer[index + 3] = r;
//	buffer[index + 4] = g;
//	buffer[index + 5] = b;
//	buffer[index + 6] = a;
//	index += LB_VERTEX_SIZE;
//
//	buffer[index] = x2;
//	buffer[index + 1] = y2;
//	buffer[index + 2] = z2;
//	buffer[index + 3] = r;
//	buffer[index + 4] = g;
//	buffer[index + 5] = b;
//	buffer[index + 6] = a;
//	index += LB_VERTEX_SIZE;
//}
//
//void LineBatch::box(float x, float y, float z, float w, float h, float d,
//	float r, float g, float b, float a) {
//	w *= 0.5f;
//	h *= 0.5f;
//	d *= 0.5f;
//
//	line(x - w, y - h, z - d, x + w, y - h, z - d, r, g, b, a);
//	line(x - w, y + h, z - d, x + w, y + h, z - d, r, g, b, a);
//	line(x - w, y - h, z + d, x + w, y - h, z + d, r, g, b, a);
//	line(x - w, y + h, z + d, x + w, y + h, z + d, r, g, b, a);
//
//	line(x - w, y - h, z - d, x - w, y + h, z - d, r, g, b, a);
//	line(x + w, y - h, z - d, x + w, y + h, z - d, r, g, b, a);
//	line(x - w, y - h, z + d, x - w, y + h, z + d, r, g, b, a);
//	line(x + w, y - h, z + d, x + w, y + h, z + d, r, g, b, a);
//
//	line(x - w, y - h, z - d, x - w, y - h, z + d, r, g, b, a);
//	line(x + w, y - h, z - d, x + w, y - h, z + d, r, g, b, a);
//	line(x - w, y + h, z - d, x - w, y + h, z + d, r, g, b, a);
//	line(x + w, y + h, z - d, x + w, y + h, z + d, r, g, b, a);
//}
//
//void LineBatch::render() {
//	if (index == 0)
//		return;
//	mesh->reload(buffer, index / LB_VERTEX_SIZE);
//	mesh->draw(GL_LINES);
//	index = 0;
//}