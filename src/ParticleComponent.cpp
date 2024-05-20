#include "particle_component.h"
#include "game_object.h"

ParticleComponent::ParticleComponent(glm::vec3* spawnPosition, glm::vec3* cameraRight, glm::vec3* cameraUp, ParticleType particleType, f32 particleCount, f32 radius, std::string texturePath){
    particlePositions.reserve(particleCount);
    this->particleCount = particleCount;
    this->particleType = particleType;
    this->spawnPosition = spawnPosition;
    this->cameraRight = cameraRight;
    this->cameraUp = cameraUp;
    this->radius = radius;

    switch(particleType){
        case PARTICLE_SPHERE:
            CreateParticleSphere();
            break;
        case PARTICLE_POINT:
            CreateParticlePoint();
            break;
    }

    shader.InitializeShader("billboard_vertex.glsl", "billboard_fragment.glsl");
    texture.InitializeFromFile(texturePath);
    renderObject.IntializeRenderObject();

    std::vector<f32> quad = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    renderObject.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, quad.data(), quad.size(), sizeof(f32));
    renderObject.BufferData(INSTANCED_BUFFER, GL_DYNAMIC_DRAW, particlePositions.data(), particlePositions.size(), sizeof(f32));
    renderObject.AddAttribute(false, true, GL_FLOAT, 2, 0, 0);
    renderObject.AddAttribute(true, true, GL_FLOAT, 3, 0, 0);
}

ParticleComponent::~ParticleComponent(){

}


void ParticleComponent::Draw(glm::mat4 projectionView, glm::mat4 transform){
    shader.UseProgram();
    texture.ActivateTexture(0);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionView));
    glUniform3fv(1, 1, glm::value_ptr(*cameraRight));
    glUniform3fv(2, 1, glm::value_ptr(*cameraUp));

    renderObject.Draw(DRAW_A_INSTANCED, GL_TRIANGLE_STRIP, 4, particleCount);
}


void ParticleComponent::CreateParticleSphere(){
    for(i32 i = 0; i < particleCount; i++){
        f32 x = std::rand();
        f32 y = std::rand() - std::rand();
        particlePositions.push_back(glm::sin(x) * radius * glm::cos(y) + spawnPosition->x);
        particlePositions.push_back(((y <= 0.0f)? 1 : -1) * glm::sin(y) * radius * glm::sin(y) + spawnPosition->y);
        particlePositions.push_back(glm::cos(x) * radius * glm::cos(y) + spawnPosition->z);  
    } 
};  

void ParticleComponent::CreateParticlePoint(){
    for(i32 i = 0; i < particleCount; i++){
        particlePositions.push_back(spawnPosition->x);
        particlePositions.push_back(spawnPosition->y);
        particlePositions.push_back(spawnPosition->z);
    }
}