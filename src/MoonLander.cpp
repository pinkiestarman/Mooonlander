#include <SDL2/SDL.h>
#include <iostream>
#include "MLhelper.h"
#include <utility>
#include <string>
#include <math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//std:: << "Get Pref Path:"<< SDL_GetPrefPath("Pinkie Starman","Mooon Lander") << "and Base Path:" << SDL_GetBasePath() << std::endl;

class Player{
    private:
        SDL_Rect prect; //Position und Größe des Players
        float veloh; //Geschwindigkeit horizontal
        float velov; //vertical speed
        double grav;
        double speedh(){
            return veloh/500;
        }
        double speedv(){
            return velov/500;
        }
    public:
        Player( int x_pos, int y_pos, int height, int width){
            veloh = 0;
            velov = 0;
            prect = {x_pos,y_pos,height,width};
            grav = .1;
        }
        double speed(){
            return fabs(velov + veloh);
        }
        int x(){
            return prect.x;
        }
        int y(){
            return prect.y;
        }
        void boostv(int d){
            velov+=d;
        };
        void boosth(int d){
            veloh+=d;
        }
        void changeDirection(){
            //velov *= -1;
            //grav += .1;
        }
        void touchsides(){
            if(prect.x <= 1 || prect.x >= SCREEN_WIDTH-(prect.w-1))veloh*=-1;
        }
        bool touchdown(){
            return (prect.y >= SCREEN_HEIGHT-(prect.h+50))?true:false;
        }
        SDL_Rect* rectp(){
            return &prect;
        }
        void update(){
            prect.x += speedh();
            prect.y += speedv();
        }
        int gravity(){
            // int dist = SCREEN_HEIGHT - prect.y;
            return grav;
        }
};
class Landing{
    private:
        int x;
        
};
// Function to calculate distance 
float distance(int x1, int y1, int x2, int y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
}

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

    Player player1(SCREEN_WIDTH/2,1,62,32);
    const int BOOST = 100;
    SDL_Event e;
    bool quit = 0;
    bool end = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                quit =true;
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {

                case SDLK_UP:
                    player1.boostv(-BOOST);
                    break;
                case SDLK_DOWN:
                    player1.boostv(BOOST);
                    break;
                case SDLK_RIGHT:
                    player1.boosth(BOOST);
                    break;
                case SDLK_LEFT:
                    player1.boosth(-BOOST);
                    break;

                default:
                    
                    break;
                }
            }
        }
               
        //player1.boostv(BOOST*player1.gravity());//Gravity
        player1.touchsides();
        player1.update();
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        if(player1.touchdown()){
            if(player1.speed() > 2000){
                SDL_SetRenderDrawColor(renderer, 200,0,0,255);
                }
            else
            {
                SDL_SetRenderDrawColor(renderer,0,200,200,SDL_ALPHA_OPAQUE);
            }
            
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, player1.rectp());
        SDL_RenderDrawLine(renderer,0,SCREEN_HEIGHT-50,SCREEN_WIDTH,SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);

    }
    cleanup(renderer,window);
     
    SDL_Quit();
    return 0;
}