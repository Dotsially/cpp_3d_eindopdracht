#include "game.h"
#include <iostream>

Game::Game(std::string title, i32 screenWidth, i32 screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->title = title;
}
Game::~Game(){}

void Game::Run(){
    Init();
    GameLoop();
    Close();
}

void Game::Init(){
    window.InitializeWindow(title, screenWidth, screenHeight);
    camera.InitializeCamera(glm::vec3{128,32,128});
    model.LoadModel("map/map.gltf");
    shader.InitializeShader("model_vertex.glsl", "model_fragment.glsl");
    texture.InitializeFromFile("terrain.png");

    ro.IntializeRenderObject();
    ro.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, model.GetVertices()->data(), model.GetVertices()->size(), sizeof(f32));
    ro.BufferData(ELEMENT_BUFFER, GL_STATIC_DRAW, model.GetIndices()->data(), model.GetIndices()->size(), sizeof(u32));
    ro.AddAttribute(false, true, GL_FLOAT, 3, 8 * sizeof(float), 0);
    ro.AddAttribute(false, true, GL_FLOAT, 3, 8 * sizeof(float), 3 * sizeof(float));
    ro.AddAttribute(false, true, GL_FLOAT, 2, 8 * sizeof(float), 6 * sizeof(float));


    glEnable(GL_DEPTH_TEST);
}

void Game::GameLoop(){
    while(!window.WindowShouldClose()){
        Update();
        Render();
    }
}

void Game::Update(){
    window.PollEvents();
    window.Update(true);
    camera.Update(glm::vec3{0,10,0});

    const u8* keystate = SDL_GetKeyboardState(NULL);
    SDL_Event e = window.GetEvent();
    if(e.type == SDL_QUIT){
        window.Quit();
    }
    else if(keystate[SDL_SCANCODE_ESCAPE]){
        window.Quit();
    }
}

void Game::Render(){
    glClearColor(0.6, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.UseProgram();
    texture.ActivateTexture(0);
    glm::mat project_view = camera.GetViewProjectionMatrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(project_view));
    ro.Draw(DRAW_ELEMENT, GL_TRIANGLES, model.GetIndices()->size());

    window.SwapBuffers();
}

void Game::Close(){
    texture.DestroyTexture();
    ro.DestroyRenderObject();
    shader.DestroyShader();
    window.DestroyWindow();
}