#include "planet_component.h"
#include "game_object.h"

PlanetComponent::PlanetComponent(glm::vec3* parent, f32 radius, f32 spinTime, f32 yearTime, f32 startOffset, f32 planetRotation){
    this->parent = parent;
    this->radius = radius;
    this->spinTime = spinTime;
    this->yearTime = yearTime;
    this->startOffset = startOffset;
    this->planetRotation = planetRotation;
}

PlanetComponent::~PlanetComponent(){

}

void PlanetComponent::Update(f32 elapsedTime){
    gameObject->position = glm::vec3(parent->x + glm::sin(startOffset + SDL_GetTicks64() * yearTime) * radius, parent->y, parent->z + glm::cos(startOffset + SDL_GetTicks64() * yearTime) * radius);
    gameObject->rotation = glm::vec3{planetRotation, SDL_GetTicks64() * spinTime, 0};
}