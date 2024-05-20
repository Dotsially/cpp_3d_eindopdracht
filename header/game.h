#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "camera.h"
#include "window.h"
#include "model.h"
#include "game_object.h"
#include "model_component.h"
#include "unshaded_model_component.h"
#include "planet_component.h"
#include "spaceship_component.h"
#include "follow_component.h"
#include "particle_component.h"

//Box data together
struct Background{
    RenderObject render;
    Texture texture;
    Shader shader;
};

class Game{
private:
    std::string title = "";
    i32 screenWidth = 0;
    i32 screenHeight = 0;
    f64 lastFrameTime = 0;

    Window window;
    Camera camera;
    Background ui;
    std::vector<GameObject*> gameObjects;
    

    void Init();
    void Update();
    void Render();
    void Close();
public:
    Game(std::string title, i32 screenWidth, i32 screenHeight);
    ~Game();
    void Run();
};