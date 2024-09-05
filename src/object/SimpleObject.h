#pragma once
#include "BaseObject.h"

class SimpleObject : public BaseObject {
protected:
    glm::ivec3 position;
    glm::vec3 offset;

public:
	SimpleObject(const glm::ivec3& position, const glm::vec3& offset);
	virtual ~SimpleObject() = default;

    glm::ivec3 getPosition() const;
    glm::vec3 getOffset() const;

    virtual void setPosition(const glm::ivec3& position);
    virtual void setOffset(const glm::vec3& offset);

protected:
    virtual void move(const glm::vec3& position);

private:
    virtual void updatePosition();

};