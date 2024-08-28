#include "Mesh.h"

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

//void Mesh::build(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, GLenum usage)
//{
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    if (!vertices.empty()) {
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], usage);
//    }
//    else {
//        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, usage);
//    }
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    if (!indices.empty()) {
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], usage);
//    }
//    else {
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, usage);
//    }
//
//    if (!vertices.empty()) {
//        vertices[0].attrib();
//    }
//    count = indices.size();
//
//    glBindVertexArray(0);
//}

//void Mesh::build(const std::vector<Vertex*>& vertices, const std::vector<unsigned int>& indices, GLenum usage)
//{
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    if (!vertices.empty()) {
//        // Определяем размер данных в зависимости от типа вершин
//        std::vector<GLbyte> buffer;
//        size_t vertex_size = 0;
//
//        // Определяем размер для всех вершин
//        if (dynamic_cast<VertexPoint*>(vertices[0])) {
//            vertex_size = sizeof(VertexPoint);
//        }
//        else if (dynamic_cast<VertexMesh*>(vertices[0])) {
//            vertex_size = sizeof(VertexMesh);
//        }
//
//        // Создаем буфер с данными вершин
//        for (const auto& vertex : vertices) {
//            const GLbyte* start = reinterpret_cast<const GLbyte*>(vertex);
//            buffer.insert(buffer.end(), start, start + vertex_size);
//        }
//        glBufferData(GL_ARRAY_BUFFER, buffer.size(), buffer.data(), usage);
//    }
//    else {
//        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, usage);
//    }
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    if (!indices.empty()) {
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), usage);
//    }
//    else {
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, usage);
//    }
//
//    if (!vertices.empty()) {
//        // Устанавливаем атрибуты для первой вершины (предполагаем, что все вершины одного типа)
//        vertices[0]->attrib();
//    }
//    count = indices.size();
//
//    glBindVertexArray(0);
//}

void Mesh::build(const std::vector<VertexPoint*>& vertices, const std::vector<unsigned int>& indices, GLenum usage) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (!vertices.empty()) {
        std::vector<GLbyte> buffer;
        for (const auto& vertex : vertices) {
            GLbyte* start = reinterpret_cast<GLbyte*>(vertex);
            buffer.insert(buffer.end(), start, start + sizeof(*vertex));
        }
        glBufferData(GL_ARRAY_BUFFER, buffer.size(), buffer.data(), usage);
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

    if (!vertices.empty()) {
        vertices[0]->attrib();
    }
    count = indices.size();

    glBindVertexArray(0);
}

void Mesh::build(const std::vector<VertexMesh*>& vertices, const std::vector<unsigned int>& indices, GLenum usage) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (!vertices.empty()) {
        std::vector<GLbyte> buffer;
        for (const auto& vertex : vertices) {
            GLbyte* start = reinterpret_cast<GLbyte*>(vertex);
            buffer.insert(buffer.end(), start, start + sizeof(*vertex));
        }
        glBufferData(GL_ARRAY_BUFFER, buffer.size(), buffer.data(), usage);
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

    if (!vertices.empty()) {
        vertices[0]->attrib();
    }
    count = indices.size();

    glBindVertexArray(0);
}

void Mesh::render(GLenum primitive) const
{
    glBindVertexArray(VAO);
    glDrawElements(primitive, static_cast<unsigned int>(count), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}