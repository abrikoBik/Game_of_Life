#include "game.h"

bool simulationStart = false;
bool drawing = false;
int mouseX,mouseY;

void Game::Init(std::string title, int windowPosX, int windowPosY) 
{   
    if(IMG_Init(IMG_INIT_PNG) < 0) 
    {
        printf("SDL Image could not initialize! SDL Error %s\n", IMG_GetError());
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error %s\n", SDL_GetError());
        quit = true;
    } 
    else
    {
        window = SDL_CreateWindow(title.c_str(), windowPosX, windowPosY, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        // Set icon to window
        SDL_Surface* icoSurface = IMG_Load("./data/icon.png");

        SDL_SetWindowIcon(window, icoSurface);

        SDL_FreeSurface(icoSurface);

        if(window == 0) 
        {
            printf("Window wasn't created! SDL Error %s\n", SDL_GetError());
            quit = true;
        }
        else 
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer == 0)
            {
                printf("Renderer wasn't created! SDL Error %s\n", SDL_GetError());
                quit = true;
            } else 
            {
                
            }

        }
    }

}

void Game::HandleEvent()
{
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {   
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                simulationStart = event.key.keysym.sym == SDLK_e;
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouseX, &mouseY);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT && !simulationStart) {
                    drawing = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    drawing = false;
                }
                break;
            default:
                break;
        }
    }
}

void Game::Update() 
{
    if(drawing) grid[mouseY/gridSize][mouseX/gridSize] = true;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    for(int y = 0; y < SCREEN_HEIGHT/gridSize; y++) 
    {
        for(int x = 0; x < SCREEN_WIDTH/gridSize; x++) 
        {
            if(simulationStart) {
                Uint8 neighborSum =     grid[y+1][x] + grid[y+1][x+1] + grid[y+1][x-1] + 
                                        grid[y][x+1] + grid[y][x-1] + 
                                        grid[y-1][x] + grid[y-1][x+1] + grid[y-1][x+1];

                if(grid[y][x]) {
                    if(neighborSum < 2) grid[y][x] = false;
                    else if(neighborSum > 3) grid[y][x] = false;
                } else {
                    if(neighborSum >= 3) grid[y][x] = true;
                }
            }

            if(grid[y][x]) {
                SDL_Rect r;
                r.x = x * gridSize;
                r.y = y * gridSize;
                r.w = gridSize;
                r.h = gridSize;
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}