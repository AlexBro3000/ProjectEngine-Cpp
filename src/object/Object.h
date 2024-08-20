#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Object
{
protected:
    glm::vec3 position;
    glm::ivec3 position_offset;
    glm::vec3 rotation;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

protected:
    Object(const glm::vec3& position = glm::vec3(0.0f), const glm::ivec3& position_offset = glm::ivec3(0), const glm::vec3& rotation = glm::vec3(0.0f));
    virtual ~Object() = default;

public:
    void setPosition(const glm::vec3& position, const glm::ivec3& position_offset);
    void setRotation(const glm::vec3& rotation);

    glm::vec3 getPosition() const;
    glm::ivec3 getPositionOffset() const;
    glm::vec3 getRotation() const;

    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    void move(const glm::vec3& position);
    void rotate(const glm::vec3& rotation);

private:
    void updatePosition();
    void updateRotation();

};