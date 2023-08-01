#pragma once

#include "iostream"
#include "string"

#include "SDL.h"
#include "SDL_image.h"

class Game {

public:

    bool quit = false;;

    Game(const int screenWidth = 800, const int screenHeight = 600) : SCREEN_WIDTH(screenWidth), SCREEN_HEIGHT(screenHeight) {}

    ~Game();

    void Init(std::string title, int windowPosX = SDL_WINDOWPOS_CENTERED, int windowPosY = SDL_WINDOWPOS_CENTERED);
    void Render();
    void HandleEvent(); 
    void Update();
    void Clear();

    void setBGColor(SDL_Color color) { bgColor = color; }

private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    SDL_Color bgColor = { 0, 0, 0, SDL_ALPHA_OPAQUE};

    static const int gridSize = 5;
    bool grid[600/gridSize][800/gridSize] = { 0 };

};