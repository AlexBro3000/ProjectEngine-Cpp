#include "Mesh.h"

////////////////////////////////////////////////////////////////////////////////
/////     VERTEX                                                           /////
////////////////////////////////////////////////////////////////////////////////

void Vertex::Attrib()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));

    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, texture_id));
}

////////////////////////////////////////////////////////////////////////////////
/////     MESH                                                             /////
////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh() :
    VAO(0), VBO(0), EBO(0), count(0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::build(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, GLenum usage)
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], usage);

    Vertex::Attrib();
    count = indices.size();

    glBindVertexArray(0);
}

void Mesh::render(GLenum primitive) const
{
    glBindVertexArray(VAO);
    glDrawElements(primitive, static_cast<unsigned int>(count), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}