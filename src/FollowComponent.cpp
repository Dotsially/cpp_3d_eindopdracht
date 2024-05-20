#include "follow_component.h"
#include "game_object.h"



FollowComponent::FollowComponent(glm::vec3* parent){
    this->parent = parent;
}


FollowComponent::~FollowComponent(){

}


void FollowComponent::Update(f32 elapsedTime){
    gameObject->position = *parent;
}