#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "../../graphic/mesh/Vertex.h"

template <typename VertexType>
class Mesh {
private:
    std::vector<VertexType> vertices;
    std::vector<unsigned int> indices;

    GLuint VAO, VBO, EBO;
    size_t count;

public:
    Mesh() : VAO(0), VBO(0), EBO(0), count(0) {}
    Mesh(const std::vector<VertexType> vertices, const std::vector<unsigned int> indices)
        : vertices(vertices), indices(indices), VAO(0), VBO(0), EBO(0), count(0) {}
    ~Mesh();

    void build(GLenum usage, bool f_clear_data = true);
    void render(GLenum primitive = GL_TRIANGLES) const;

    const std::vector<VertexType>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    void setData(const std::vector<VertexType>& vertices, const std::vector<unsigned int>& indices);

    void clear();

private:
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;
};



template<typename VertexType>
Mesh<VertexType>::~Mesh()
{
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    Mesh::clear();
}

template<typename VertexType>
void Mesh<VertexType>::build(GLenum usage, bool f_clear_data)
{
    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (!vertices.empty()) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), usage);
        vertices[0].attrib();
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, usage);
    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    if (!indices.empty()) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), usage);
    }
    else {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, usage);
    }

    count = indices.size();

    glBindVertexArray(0);

    if (f_clear_data) {
        clear();
    }
}

template<typename VertexType>
void Mesh<VertexType>::render(GLenum primitive) const
{
    glBindVertexArray(VAO);
    glDrawElements(primitive, static_cast<unsigned int>(count), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

template<typename VertexType>
const std::vector<VertexType>& Mesh<VertexType>::getVertices() const
{
    return vertices;
}

template<typename VertexType>
const std::vector<unsigned int>& Mesh<VertexType>::getIndices() const
{
    return indices;
}

template<typename VertexType>
void Mesh<VertexType>::setData(const std::vector<VertexType>& vertices, const std::vector<unsigned int>& indices)
{
    Mesh::clear();
    this->vertices = vertices;
    this->indices = indices;
}

template<typename VertexType>
void Mesh<VertexType>::clear()
{
    this->vertices.clear();
    this->indices.clear();
}