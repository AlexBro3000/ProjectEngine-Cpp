#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    virtual ~Vertex() = default;

    virtual void attrib() const = 0;
};

// VertexPoint: Вершина для точек с координатами и цветом
struct VertexPoint : public Vertex {
    glm::vec3 position;
    glm::vec4 color;

    VertexPoint(glm::vec3 position, glm::vec4 color)
        : position(position), color(color) {}

    VertexPoint(const VertexPoint& other)
        : position(other.position), color(other.color) {}

    VertexPoint& operator=(const VertexPoint& other) {
        if (this != &other) {
            position = other.position;
            color = other.color;
        }
        return *this;
    };

    void attrib() const override {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), (void*)offsetof(VertexPoint, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPoint), (void*)offsetof(VertexPoint, color));
    }
};

// VertexMesh: Вершина для меша с текстурными координатами и ID текстуры
struct VertexMesh : public Vertex {
    glm::vec3 position;
    glm::vec2 texture_coords;
    int texture_id;

    VertexMesh(glm::vec3 position, glm::vec2 texture_coords, int texture_id)
        : position(position), texture_coords(texture_coords), texture_id(texture_id) {}

    void attrib() const override {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, texture_coords));

        glEnableVertexAttribArray(2);
        glVertexAttribIPointer(2, 1, GL_INT, sizeof(VertexMesh), (void*)offsetof(VertexMesh, texture_id));
    }
};



class Mesh
{
private:
    GLuint VAO, VBO, EBO;
    size_t count;

public:
    Mesh();
    ~Mesh();

    //void build(const std::vector<Vertex*>& vertices, const std::vector<unsigned int>& indices, GLenum usage);
    void build(const std::vector<VertexPoint*>& vertices, const std::vector<unsigned int>& indices, GLenum usage);
    void build(const std::vector<VertexMesh*>& vertices, const std::vector<unsigned int>& indices, GLenum usage);
    void render(GLenum primitive = GL_TRIANGLES) const;

private:
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;
};