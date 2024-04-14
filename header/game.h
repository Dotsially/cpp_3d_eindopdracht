#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "camera.h"
#include "window.h"

class Game{
private:
    std::string title = "";
    i32 screenWidth = 0;
    i32 screenHeight = 0;
    Window window;
    Camera camera;

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