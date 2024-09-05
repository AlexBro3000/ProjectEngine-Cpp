#include "Vertex.h"

void Vertex::attrib() const
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
}

size_t Vertex::size() const
{
    return sizeof(Vertex);
}



VertexPoint& VertexPoint::operator=(const VertexPoint& other)
{
    if (this != &other) {
        position = other.position;
        color = other.color;
    }
    return *this;
}

void VertexPoint::attrib() const
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), (void*)offsetof(VertexPoint, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), (void*)offsetof(VertexPoint, color));
}

size_t VertexPoint::size() const
{
    return sizeof(VertexPoint);
}



VertexMesh& VertexMesh::operator=(const VertexMesh& other)
{
    if (this != &other) {
        position = other.position;
        texture_coords = other.texture_coords;
        texture_id = other.texture_id;
    }
    return *this;
}

void VertexMesh::attrib() const
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, texture_coords));

    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(VertexMesh), (void*)offsetof(VertexMesh, texture_id));
}

size_t VertexMesh::size() const
{
    return sizeof(VertexMesh);
}