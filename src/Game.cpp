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

    GameObject* spaceShip = new GameObject();
    spaceShip->AddDrawComponent(new ModelComponent("spaceship/spaceship.gltf", "spaceship_palette.png"));
    spaceShip->AddComponent(new SpaceshipComponent(camera.GetAngle()));
    spaceShip->position = glm::vec3(0.0f, 4.0f, 0.5f);
    spaceShip->scale = glm::vec3(0.1f);
    gameObjects.push_back(spaceShip);

    GameObject* stars = new GameObject();
    stars->AddDrawComponent(new ParticleComponent(&spaceShip->position, camera.GetRight(), camera.GetUp(), PARTICLE_SPHERE, 10000, 200, "star.png"));
    gameObjects.push_back(stars);

    GameObject* skybox = new GameObject();
    skybox->AddDrawComponent(new UnshadedModelComponent("skybox/skybox.gltf", "gradient.png"));
    skybox->scale = glm::vec3{900.0f};
    gameObjects.push_back(skybox);  

    GameObject* sun = new GameObject();
    sun->AddDrawComponent(new UnshadedModelComponent("sun/sun.gltf", "planet_palette.png"));
    sun->scale = glm::vec3{1.6};
    gameObjects.push_back(sun);

    GameObject* gasGiant = new GameObject();
    gasGiant->AddDrawComponent(new ModelComponent("gasgiant/gas_giant.gltf", "planet_palette.png"));
    gasGiant->AddComponent(new PlanetComponent(&sun->position, 70.0f, 0.001f, 0.00009f, 23, 0.0f));
    gasGiant->scale = glm::vec3{2.5};
    gameObjects.push_back(gasGiant);

    GameObject* ringPlanet = new GameObject();
    ringPlanet->AddDrawComponent(new ModelComponent("ringplanet/ring_planet.gltf", "planet_palette.png"));
    ringPlanet->AddComponent(new PlanetComponent(&sun->position, 50.0f, 0.002f, 0.00005f, 10, glm::radians(15.0f)));
    ringPlanet->scale = glm::vec3{1.5};
    gameObjects.push_back(ringPlanet);

    GameObject* earthLike = new GameObject();
    earthLike->AddDrawComponent(new ModelComponent("earthlike/earth_like.gltf", "planet_palette.png"));
    earthLike->AddComponent(new PlanetComponent(&sun->position, 26.0f, 0.003f, 0.0001f, 5, glm::radians(23.5f)));
    gameObjects.push_back(earthLike);

    GameObject* moon = new GameObject();
    moon->AddDrawComponent(new ModelComponent("moon/moon.gltf", "planet_palette.png"));
    moon->AddComponent(new PlanetComponent(&earthLike->position, 2.0f, 0.002f, 0.001f, 0, 0.0f));
    moon->scale = glm::vec3(0.4f);
    gameObjects.push_back(moon);

    GameObject* barren = new GameObject();
    barren->AddDrawComponent(new ModelComponent("barren/barren.gltf", "planet_palette.png"));
    barren->AddComponent(new PlanetComponent(&sun->position, 8.0f, 0.002f, 0.00009f, 65, 0.0f));
    gameObjects.push_back(barren);

    camera.InitializeCamera(&spaceShip->position);
    
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

    camera.Update();
}

void Game::Render(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projectionView = camera.GetViewProjectionMatrix();
    for(auto gameObject : gameObjects){
        gameObject->Draw(projectionView);
    }

    window.SwapBuffers();
}

void Game::Close(){
    window.DestroyWindow();
}