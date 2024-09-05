#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

template <typename VertexType>
class Batch {
protected:
    std::vector<VertexType> vertices;
    std::vector<unsigned int> indices;

    GLuint VAO, VBO, EBO;
    size_t count;

public:
    Batch() : VAO(0), VBO(0), EBO(0), count(0) {}
    virtual ~Batch();

protected:
    virtual void build(GLenum usage, bool f_clear_data = true);
    virtual void render(GLenum primitive) const;

    virtual void clear();

private:
    Batch(const Batch&) = delete;
    Batch(Batch&&) = delete;

    Batch& operator=(const Batch&) = delete;
    Batch& operator=(Batch&&) = delete;
};



template<typename VertexType>
inline Batch<VertexType>::~Batch()
{
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    Batch::clear();
}

template<typename VertexType>
inline void Batch<VertexType>::build(GLenum usage, bool f_clear_data)
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
        Batch::clear();
    }
}

template<typename VertexType>
inline void Batch<VertexType>::render(GLenum primitive) const
{
    glBindVertexArray(VAO);
    glDrawElements(primitive, static_cast<unsigned int>(count), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

template<typename VertexType>
inline void Batch<VertexType>::clear()
{
    this->vertices.clear();
    this->indices.clear();
}