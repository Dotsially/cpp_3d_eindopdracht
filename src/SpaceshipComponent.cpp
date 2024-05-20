#include "spaceship_component.h"
#include "game_object.h"
#include "SDL2/SDL.h"
#include "glm/gtx/compatibility.hpp"

SpaceshipComponent::SpaceshipComponent(glm::vec2* cameraAngle){
    this->cameraAngle = cameraAngle;
    oldAngle = cameraAngle->x;
}

SpaceshipComponent::~SpaceshipComponent(){

}

void SpaceshipComponent::Update(f32 elapsedTime){
    f32 deltaAngle = oldAngle - cameraAngle->x;
    oldAngle = cameraAngle->x;
    rotationAngle += deltaAngle * 0.2f;

    rotationAngle = glm::clamp(rotationAngle, glm::radians(-90.0f), glm::radians(90.0f));
    if(deltaAngle == 0.0f){

        interpolationFrame += 0.0001f * elapsedTime;
        rotationAngle = glm::lerp(rotationAngle, 0.0f, interpolationFrame);
    }
    else{
        interpolationFrame = 0.0f;
    }

    gameObject->rotation = glm::vec3(0.0f, cameraAngle->x + glm::radians(180.0f), rotationAngle);


    glm::vec2 vectorAngleRotation = glm::vec2(sinf(cameraAngle->x),cosf(cameraAngle->x));
    
    const u8* keystate = SDL_GetKeyboardState(NULL);
    
    if(keystate[SDL_SCANCODE_SPACE]){
        gameObject->position -= glm::vec3(vectorAngleRotation.x, 0.0f, vectorAngleRotation.y) * elapsedTime * 0.01f;
    }
    else if(keystate[SDL_SCANCODE_LSHIFT]){
        gameObject->position += glm::vec3(vectorAngleRotation.x, 0.0f, vectorAngleRotation.y) * elapsedTime * 0.01f;    
    }

}