#pragma once
#include "depedencies.h"
#include "component.h"
#include "glm/glm.hpp"



class SpaceshipComponent : public Component
{
private:
    glm::vec2* cameraAngle;
	f32 oldAngle;
	f32 rotationAngle = 0.0f;
	f32 interpolationFrame = 0.0f;
public:
	SpaceshipComponent(glm::vec2* cameraAngle);
	~SpaceshipComponent();

	virtual void Update(f32 elapsedTime) override;
};
