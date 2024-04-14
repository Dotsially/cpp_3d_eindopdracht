#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "camera.h"
#include "window.h"
#include "world.h"
#include "model.h"

class Game{
private:
    std::string title = "";
    i32 screenWidth = 0;
    i32 screenHeight = 0;
    Window window;
    Camera camera;
    Model model;
    Shader shader;
    Texture texture;
    RenderObject ro;

    void Init();
    void GameLoop();
    void Update();
    void Render();
    void Close();
public:
    Game(std::string title, i32 screenWidth, i32 screenHeight);
    ~Game();
    void Run();
};