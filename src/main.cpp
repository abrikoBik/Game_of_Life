#include "iostream"
#include "SDL.h"
#include "game.h"

Game* game;

int main(int argc, char* argv[])
{

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameTime;
    int frameStart;

    game = new Game(1280,720);

    game->Init("Cellular Automata Engine");

    while(!game->quit) 
    {
        frameStart = SDL_GetTicks();

        game->Render();
        game->HandleEvent();
        game->Update();

        frameTime = SDL_GetTicks() - frameStart;
        printf("Frame time - %i ms\n", frameTime);
        if(frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }

    game->Clear();
    
    return 0;
}