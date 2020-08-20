#include "SDL2/SDL.h"
#include "iostream"
//#include "MLhelper.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//SDL_Init Error logger
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << "SDL_GetError()" << std::endl;
}

class player{
    public:
        int h;
        int w;
        float x;
        float y; //Position und Größe des Players
        float veloh; //Geschwindigkeit
        float velov;
};
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Moon Lander", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer");
        SDL_Quit();
        return 1;
    }


    

    player player1;
    player1.h = 22;
    player1.w = 32;
    player1.x = SCREEN_WIDTH/2;
    player1.y = 2;
    player1.veloh = 0;
    player1.velov = 0;

    SDL_Rect player1Rect;
    player1Rect.h = player1.h;
    player1Rect.w = player1.w;
    
    SDL_Event e;
    bool quit = 0;
    while (!quit)
    {
        player1Rect.x = player1.x;
        player1Rect.y = player1.y;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {

                case SDLK_UP:
                    player1.velov-=.1;
                    break;
                case SDLK_DOWN:
                    player1.velov+=.1;
                    break;
                case SDLK_RIGHT:
                    player1.veloh+=.1;
                    break;
                case SDLK_LEFT:
                    player1.veloh-=.1;
                    break;

                default:
                    player1.velov+=.1;
                    break;
                }

            }
        }
        if(player1.veloh > 3) player1.veloh=3;
        if(player1.veloh < -3) player1.veloh=-3;
        if(player1.velov > 3) player1.velov=3;
        if(player1.velov < -3) player1.velov=-3;
        if(player1.x <=0 || player1.x >= SCREEN_WIDTH-player1.w) player1.veloh *= -1;
        if(player1.y <=0 || player1.y >= SCREEN_HEIGHT-player1.h) player1.velov *= -1;
        player1.x+=player1.veloh;
        player1.y+=player1.velov;
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player1Rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
    //cleanup(renderer,window);
    SDL_Quit();
    return 0;
}