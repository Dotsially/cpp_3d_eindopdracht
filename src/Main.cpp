/*
C++ en Datastructuren:
 - File IO 
    Shader.cpp at LoadShaderFromFile() ifstream
    Model.cpp at LoadModel() ifstream
 - Inheritance:
    component.h
    draw_component.h
    model_component.h
 - 'Constructor':
    Game.cpp
    PlanetComponent.cpp
 - Virtual function:
    draw_component.h
 - Geen memory leaks + new gebruikt
 - Exceptions:
    Shader.cpp
    Main.cpp

3D Graphics:
 - OpenGL met VAOs gebruikt:
    render_object.h  
    RenderObject.cpp
    shader.h
    Shader.cpp
    texture.h
    Texture.cpp
 -  De scene bestaat uit meerdere planeten, manen, zon en een spaceship.
    Alle planeten draaien om de zon heen. 
    Alle manen draaiem om een planeet heen.
    Alle planeten en manen zijn een custom model met texture mapping.
    De gebruiker kan vrij zijn/haar camera draaien en de spaceship besturen.
    Alle planeten en de spaceship worden belicht door de zon.
 -  Lighting: 
    Er wordt gebruikt gemaakt van Gouraud shading.
 -  Alpha blending:
    De UI maakt gebruikt van alpha blending.
 - 
Controls:
   -Space: Forward
   -Left Shift: Backwards
   -Mouse: Rotate ship.
*/
#define SDL_MAIN_HANDLED
#define FNL_IMPL
#include "game.h"
#include <iostream>

int main(int argc, char* args[]){
    Game game("Eindopdracht", 1280, 720);
    try {
        game.Run();
    }
    catch(std::exception e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}