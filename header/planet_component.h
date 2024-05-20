#pragma once
#include "depedencies.h"
#include "component.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"


class PlanetComponent : public Component
{
private:
    glm::vec3* parent = nullptr;
    f32 radius = 0.0f;
    f32 spinTime = 0.0f;
    f32 yearTime = 0.0f;
    f32 startOffset = 0.0f;
    f32 planetRotation = 0.0f;
public:
	PlanetComponent(glm::vec3* parent, f32 radius, f32 spinTime, f32 yearTime, f32 startOffset, f32 planetRotation);
	~PlanetComponent();

	virtual void Update(f32 elapsedTime) override;
};
