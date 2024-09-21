#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

// Object
class Object {
protected:
	Object() = default;
	virtual ~Object() = default;

private:
};



// Object :: Simple Position system
class ObjSPs : public Object {
protected:
    glm::ivec3 position;

public:
    ObjSPs(const glm::ivec3& position) : position(position) {}
    virtual ~ObjSPs() = default;

    glm::ivec3 getPosition() const;

    virtual void setPosition(const glm::ivec3& position);

private:
};

// Object :: Complex Position system
class ObjCPs : public Object {
protected:
    glm::ivec3 position;
    glm::vec3 offset;

public:
    ObjCPs(const glm::ivec3& position, const glm::vec3& offset);
    virtual ~ObjCPs() = default;

    glm::ivec3 getPosition() const;
    glm::vec3 getOffset() const;

    virtual void setPosition(const glm::ivec3& position);
    virtual void setOffset(const glm::vec3& offset);

protected:
    virtual void updatePosition();

private:
};

// Object :: Rotation system
class ObjRs : public Object {
protected:
    glm::vec3 rotation;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;


public:
    ObjRs(const glm::vec3& rotation);
    virtual ~ObjRs() = default;

    glm::vec3 getRotation() const;
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    virtual void setRotation(const glm::vec3& rotation);

protected:
    virtual void updateRotation();

private:
};



// Object :: Static Simple Position system
// ---

// Object :: Static Complex Position system
// ---

// Object :: Static Rotation system
// ---



// Object :: Dynamic Simple Position system
// ---

// Object :: Dynamic Complex Position system
class ObjDCPs : public ObjCPs {
public:
    ObjDCPs(const glm::ivec3& position, const glm::vec3& offset) : ObjCPs(position, offset) {}
    virtual ~ObjDCPs() = default;

    virtual void move(const glm::vec3& position);

private:
};

// Object :: Dynamic Rotation system
class ObjDRs : public ObjRs {
public:
    ObjDRs(const glm::vec3& rotation) : ObjRs(rotation) {}
    virtual ~ObjDRs() = default;

    virtual void rotate(const glm::vec3& rotation);

private:
};