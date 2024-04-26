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

    while(!window.WindowShouldClose()){
        Update();
        Render();
    }

    Close();
}

void Game::Init(){
    window.InitializeWindow(title, screenWidth, screenHeight);
    camera.InitializeCamera(glm::vec3{16,0,16});

    //initialize the background
    std::vector<f32> backgroundQuad = {-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
    background.texture.InitializeFromFile("space.png");
    background.shader.InitializeShader("basic_vertex.glsl", "basic_fragment.glsl");
    background.render.IntializeRenderObject();
    background.render.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, backgroundQuad.data(), backgroundQuad.size(), sizeof(f32));
    background.render.AddAttribute(false, true, GL_FLOAT, 2,0,0);

    GameObject* earthLike = new GameObject();
    earthLike->AddDrawComponent(new ModelComponent("earthlike/earth_like.gltf", "planet_palette.png"));
    gameObjects.push_back(earthLike);
    
    glEnable(GL_DEPTH_TEST);
}

void Game::Update(){
    //Poll events
    window.PollEvents();
    const u8* keystate = SDL_GetKeyboardState(NULL);
    SDL_Event e = window.GetEvent();
    if(e.type == SDL_QUIT){
        window.Quit();
    }
    else if(keystate[SDL_SCANCODE_ESCAPE]){
        window.Quit();
    }

    //Calculate deltaTime
    f64 currentFrameTime = SDL_GetTicks64();
	f64 deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    window.Update(true);

    for(auto gameObject : gameObjects){
        gameObject->Update(deltaTime);
    }

    camera.Update(glm::vec3{0,0,0});
}

void Game::Render(){
    glClearColor(0.6, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glDepthFunc(GL_LESS);

    glm::mat4 projectionView = camera.GetViewProjectionMatrix();
    for(auto gameObject : gameObjects){
        gameObject->Draw(projectionView);
    }
    

    //Make it so the background is renderered behind every object
    glDepthFunc(GL_EQUAL);
    background.shader.UseProgram();
    background.texture.ActivateTexture(0);
    background.render.Draw(DRAW_ARRAY, GL_TRIANGLE_STRIP, 4);

    window.SwapBuffers();
}

void Game::Close(){
    window.DestroyWindow();
}