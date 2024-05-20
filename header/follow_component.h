#pragma once
#include "depedencies.h"
#include "component.h"
#include "glm/glm.hpp"



class FollowComponent : public Component
{
private:
    glm::vec3* parent = nullptr;
public:
	FollowComponent(glm::vec3* parent);
	~FollowComponent();

	virtual void Update(f32 elapsedTime) override;
};