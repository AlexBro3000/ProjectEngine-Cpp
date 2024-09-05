#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

class BaseObject {
protected:
    BaseObject() = default;
    virtual ~BaseObject() = default;

private:
};