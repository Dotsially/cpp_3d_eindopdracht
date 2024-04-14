#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include <string>

class Texture{
    u32 textureID;
    
public:
    Texture();
    ~Texture();

    void InitializeFromFile(std::string fileName);
    inline void ActivateTexture(i32 textureUnit);
};