#include "SDL2/SDL.h"
#include "iostream"
#include "MLhelper.h"
#include "math.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;




class player{
    private:
        SDL_Rect prect; //Position und Größe des Players
        float veloh; //Geschwindigkeit horizontal
        float velov; //vertical speed
        double speedh(){
            return veloh/400;
        }
        double speedv(){
            return velov/500;
        }
    public:
        player( int x_pos, int y_pos, int height, int width){
            veloh = 0;
            velov = 0;
            prect = {x_pos,y_pos,height,width};
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
            velov*=-.9;
        }
        void touchsides(){
            if(prect.x <= 1 || prect.x >= SCREEN_WIDTH-(prect.w-1))veloh*=-1;
        }
        bool touchdown(){
            return (prect.y >= SCREEN_HEIGHT-(prect.h+1))?true:false;
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
            return ((SCREEN_HEIGHT - (SCREEN_HEIGHT - prect.y))/10);
        }
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

    player player1(SCREEN_WIDTH/2,1,32,32);
    const int BOOST = 100;
    SDL_Event e;
    bool quit = 0;
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
        
        player1.boostv(BOOST*.5);//Gravity
        if(player1.touchdown()) player1.changeDirection();
        player1.touchsides();
        player1.update();
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        if(player1.touchdown() && player1.speed() > 2000 )
            SDL_SetRenderDrawColor(renderer, 200,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, player1.rectp());
        SDL_RenderPresent(renderer);
    }
    cleanup(renderer,window);
    SDL_Quit();
    return 0;
}