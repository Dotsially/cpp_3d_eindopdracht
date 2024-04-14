#include "game.h"
#include <iostream>

int main(int argc, char* args[]){
    Game game("Eindopdracht", 1280, 720);
    
    try{
        game.Run();
    }
    catch(std::exception e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}