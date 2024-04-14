#pragma once
#include "depedencies.h"
#include "glm/glm.hpp"
#include "render_object.h"
#include <vector>
#include "FastNoiseLite.h"

class TerrainChunk{
private:
    u8* heightmap;
    glm::vec2 position;
    i32 terrainSize;

    void SetHeightmap(i32 x, i32 z, u8 value);
    u8 GetHeightmap(i32 x, i32 z);
public:
    TerrainChunk();
    ~TerrainChunk();

    void InitializeTerrain(glm::vec2 position, fnl_state* noise, i32 terrainSize);
    void DestroyTerrain();
    void GenerateTerrainMesh(std::vector<u32>* vertices, std::vector<u32>* indices);
};