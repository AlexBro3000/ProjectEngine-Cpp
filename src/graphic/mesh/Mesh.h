#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texture_coords;
    int texture_id;

    Vertex(glm::vec3 position, glm::vec2 texture_coords, int texture_id) :
        position(position), texture_coords(texture_coords), texture_id(texture_id)
    {}

    static void Attrib();
};

class Mesh
{
private:
    GLuint VAO, VBO, EBO;
    size_t count;

public:
    Mesh();
    ~Mesh();

    void build(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, GLenum usage);
    void render(GLenum primitive = GL_TRIANGLES) const;

private:
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;
};