#pragma once
#include "BaseObject.h"

class AdvancedObject : public BaseObject
{
protected:
    glm::ivec3 position;
    glm::vec3 offset;
    glm::vec3 rotation;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

protected:
    AdvancedObject(const glm::ivec3& position, const glm::vec3& offset, const glm::vec3& rotation);
    virtual ~AdvancedObject() = default;

    virtual void move(const glm::vec3& position);
    virtual void rotate(const glm::vec3& rotation);

public:
    glm::ivec3 getPosition() const;
    glm::vec3 getOffset() const;
    glm::vec3 getRotation() const;

    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    virtual void setPosition(const glm::ivec3& position);
    virtual void setOffset(const glm::vec3& offset);
    virtual void setRotation(const glm::vec3& rotation);

private:
    virtual void updatePosition();
    virtual void updateRotation();

};