#define SDL_MAIN_HANDLED
<<<<<<< HEAD
#define FNL_IMPL
=======
>>>>>>> 7ba55e870f6cec8049422a1aa48775b6d91a63c9
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