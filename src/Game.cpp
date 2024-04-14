#include "game.h"


Game::Game(std::string title, i32 width, i32 height) : window(title, width, height){
    Init();
}

Game::~Game(){
    Close();
}


void Game::Run(){
    while(window.WindowShouldClose()){
        Update();
        Render();
    }
}

void Game::Init(){

}

void Game::Update(){
    window.PollEvents();
     
}

void Game::Render(){
    glClearColor(0.1, 0.2, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    window.SwapBuffers();
}

void Game::Close(){

    
}