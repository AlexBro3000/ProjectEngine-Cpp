#include "Object.h"

// Object :: Simple Position system

glm::ivec3 ObjSPs::getPosition() const
{
    return position;
}

void ObjSPs::setPosition(const glm::ivec3& position)
{
    ObjSPs::position = position;
}



// Object :: Complex Position system

ObjCPs::ObjCPs(const glm::ivec3& position, const glm::vec3& offset)
    : position(position), offset(offset)
{
    ObjCPs::updatePosition();
}

glm::ivec3 ObjCPs::getPosition() const
{
    return position;
}

glm::vec3 ObjCPs::getOffset() const
{
    return offset;
}

void ObjCPs::setPosition(const glm::ivec3& position)
{
    ObjCPs::position = position;
    ObjCPs::updatePosition();
}

void ObjCPs::setOffset(const glm::vec3& offset)
{
    ObjCPs::offset = offset;
    ObjCPs::updatePosition();
}

void ObjCPs::updatePosition()
{
    for (int i = 0; i < 3; i++) {
        if (offset[i] >= 1.0f) {
            int delta = static_cast<int>(offset[i]);
            position[i] += delta;
            offset[i] -= delta;
        }
        else if (offset[i] < 0.0f) {
            int delta = static_cast<int>(-offset[i]) + 1;
            position[i] -= delta;
            offset[i] += delta;
        }
    }
}



// Object :: Rotation system

ObjRs::ObjRs(const glm::vec3& rotation)
    : rotation(rotation)
{
    ObjRs::updateRotation();
}

glm::vec3 ObjRs::getRotation() const
{
    return rotation;
}

glm::vec3 ObjRs::getForward() const
{
    return forward;
}

glm::vec3 ObjRs::getRight() const
{
    return right;
}

glm::vec3 ObjRs::getUp() const
{
    return up;
}

void ObjRs::setRotation(const glm::vec3& rotation)
{
    ObjRs::rotation = rotation;
    ObjRs::updateRotation();
}

void ObjRs::updateRotation()
{
    for (int i = 0; i < 3; i++) {
        rotation[i] = glm::mod(rotation[i], 360.0f);
    }

    glm::quat quat = glm::quat(glm::radians(rotation));
    forward = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
    right = glm::normalize(glm::rotate(quat, glm::vec3(1.0f, 0.0f, 0.0f)));
    up = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 1.0f, 0.0f)));
}



// Object :: Dynamic Complex Position system

void ObjDCPs::move(const glm::vec3& position)
{
    ObjDCPs::offset += position;
    ObjDCPs::updatePosition();
}



// Object :: Dynamic Rotation system

void ObjDRs::rotate(const glm::vec3& rotation)
{
    ObjDRs::rotation += rotation;
    ObjDRs::updateRotation();
}