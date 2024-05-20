#include "camera.h"
#include <iostream>

Camera::Camera(){ }

Camera::~Camera(){ }

void Camera::InitializeCamera(glm::vec3* targetPosition){
    this->targetPosition = targetPosition;

    position = glm::vec3(0.0f);
    target = glm::vec3(0.0f);
    worldUp = glm::vec3(0.0f,1.0f,0.0f);
    fov = glm::radians(45.0);
    angle = glm::vec2(0.0f);
    zoomLevel = 8.0f;
}

void Camera::Update(){    
    int x;
    int y;
    SDL_GetRelativeMouseState(&x,&y);
    
    angle += glm::vec2(glm::radians(f32(x)),glm::radians(f32(y)));

    if(angle.y > glm::radians(89.0f)){
        angle.y = glm::radians(89.0f);
    }
    if(angle.y < glm::radians(-89.0f)){
        angle.y = glm::radians(-89.0f);
    }

    target = *targetPosition + glm::vec3(0.0f, 0.5f, 0.0f);
    position.x = glm::sin(angle.x) * zoomLevel * glm::cos(angle.y) + target.x;
    position.y = ((angle.y <= 0.0f)? 1 : -1) * glm::sin(angle.y) * zoomLevel * glm::sin(angle.y) + target.y;
    position.z = glm::cos(angle.x) * zoomLevel * glm::cos(angle.y) + target.z;

    forward = glm::normalize(target-position); 
    right = glm::normalize(glm::cross(forward, up));
    up = glm::normalize(glm::cross(right, forward));
}    

glm::mat4 Camera::GetViewProjectionMatrix(){
    glm::mat4 view = glm::lookAt(position, target, worldUp);
    glm::mat4 projection = glm::perspective(fov, 1280.0f/720.0f, 0.01f, 1000.0f);
    return projection * view;
}

glm::vec3* Camera::GetPosition(){    
    return &position;
}

glm::vec3* Camera::GetTarget(){
    return &target;
}       

glm::vec3* Camera::GetUp(){
    return &up;
}

glm::vec3* Camera::GetRight(){
    return &right;
}

glm::vec2* Camera::GetAngle(){
    return &angle;
}

f32 Camera::GetFov(){
    return fov;
}