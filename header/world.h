#pragma once
#include "depedencies.h"
#include "shader.h"
#include "texture.h"
#include "terrain.h"
#include "FastNoiseLite.h"



class World{
private:
    Shader terrainShader;
    Texture terrainTexture;
    
    RenderObject terrainMesh;
    std::vector<u32> vertices;
    std::vector<u32> indices;
    std::vector<DrawElementsIndirectCommand> commands;
    std::vector<f32> worldPositions;
    TerrainChunk* terrain;
    i32 worldSize;
public:
    World();
    ~World();

    void InitializeWorld(i32 worldSize);
    void DestroyWorld();
    void Draw(glm::mat4 projectionView);
};