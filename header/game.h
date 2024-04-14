#pragma once
#include "depedencies.h"
#include "window.h"
#include "glad/glad.h"

class Game{
private:
    Window window;

    void Init();
    void Update();
    void Render();
    void Close();
public:
    Game(std::string title, i32 width, i32 height);
    ~Game();
    void Run();
};