#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position){
    this->position = position;
    this->target = glm::vec3{5.0f,0.0f,5.0f};
    this->up = glm::vec3{0.0f,1.0f,0.0f};;
    this->fov = glm::radians(60.0);
    this->angle = glm::vec2(0,0);
}

Camera::~Camera(){
    
}


void Camera::Update(const u8* keystate, glm::vec3 targetPosition){    
    int x;
    int y;
    SDL_GetRelativeMouseState(&x,&y);


    position = targetPosition + glm::vec3(glm::cos(angle.x)*12.0, 12.0 ,sin(angle.y)*12.0) + 0.5f;
    target = targetPosition;

    forward = -glm::normalize(position - target);
    right = glm::normalize(glm::cross(forward, glm::vec3(0,1,0)));
    up =  glm::normalize(glm::cross(right, forward));
}    

glm::mat4 Camera::GetViewProjectionMatrix(){
    glm::mat4 view = glm::lookAt(position, position + target, up);
    glm::mat4 projection = glm::perspective(fov, 1280.0f/720.0f, 0.01f, 1000.0f);
    return projection * view;
}

glm::vec3 Camera::GetPosition(){    
    return position;
}

glm::vec3 Camera::GetForward(){
    return forward;
}

glm::vec3 Camera::GetTarget(){
    return target;
}       

glm::vec3 Camera::GetRight(){
    return right;
}

glm::vec3 Camera::GetUp(){
    return up;
}

f32 Camera::GetFov(){
    return fov;
}