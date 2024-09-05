#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;

    Vertex(glm::vec3 position = glm::vec3(0.0f))
        : position(position) {}

    virtual void attrib() const;
    virtual size_t size() const;
};



struct VertexPoint : public Vertex {
    glm::vec4 color;

    VertexPoint(glm::vec3 position = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
        : Vertex(position), color(color) {}

    VertexPoint(const VertexPoint& other)
        : Vertex(other.position), color(other.color) {}

    VertexPoint& operator=(const VertexPoint& other);

    void attrib() const override;
    size_t size() const override;
};

struct VertexMesh : public Vertex {
    glm::vec2 texture_coords;
    int texture_id;

    VertexMesh(glm::vec3 position = glm::vec3(0.0f), glm::vec2 texture_coords = glm::vec2(0.0f), int texture_id = 0)
        : Vertex(position), texture_coords(texture_coords), texture_id(texture_id) {}

    VertexMesh(const VertexMesh& other)
        : Vertex(other.position), texture_coords(other.texture_coords), texture_id(other.texture_id) {}

    VertexMesh& operator=(const VertexMesh& other);

    void attrib() const override;
    size_t size() const override;
};