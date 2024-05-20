#pragma once
#include "depedencies.h"
#include "draw_component.h"
#include "shader.h"
#include "render_object.h"
#include "texture.h"
#include <vector>

enum ParticleType{
    PARTICLE_SPHERE,
    PARTICLE_POINT,
};

class ParticleComponent : public DrawComponent
{
private:
    Shader shader;
    Texture texture;
    RenderObject renderObject;
    glm::vec3* spawnPosition;
    glm::vec3* cameraRight;
    glm::vec3* cameraUp;
    f32 particleCount = 0.0f;
    f32 radius = 1.0f;

    void CreateParticleSphere();
    void CreateParticlePoint();

public:
	ParticleComponent(glm::vec3* spawnPosition, glm::vec3* cameraRight, glm::vec3* cameraUp, ParticleType particleType, f32 particleCount, f32 radius, std::string texturePath);
	~ParticleComponent();

	virtual void Draw(glm::mat4 projectionView, glm::mat4 transform) override;

    ParticleType particleType;
    std::vector<f32> particlePositions; 
};