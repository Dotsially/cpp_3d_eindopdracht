#include "game.h"


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
    camera.Initialize(glm::vec3{0,0,3});
}

void Game::GameLoop(){
    while(!window.WindowShouldClose()){
        Update();
        Render();
    }
}



void Game::Update(){
    window.PollEvents();
    
    SDL_Event e = window.GetEvent();
    if(e.type == SDL_QUIT){
        window.Quit();
    }
}

void Game::Render(){
    glClearColor(0.7, 0.8, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    window.SwapBuffers();
}

void Game::Close(){
    window.DestroyWindow();
    
}