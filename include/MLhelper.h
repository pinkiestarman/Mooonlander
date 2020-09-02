#include <utility>
#include "SDL2/SDL.h"
#include <iostream>

//SDL_Init Error logger
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << "SDL_GetError()" << std::endl;
}
//Cleanup function template
template<typename T, typename... Args>
void cleanup(T *t, Args&&... args){
	//Cleanup the first item in the list
	cleanup(t);
	//Recurse to clean up the remaining arguments
	cleanup(std::forward<Args>(args)...);
}
/*
 *
 */
template<>
inline void cleanup<SDL_Window>(SDL_Window *win){
	if (!win){
		return;
	}
	SDL_DestroyWindow(win);
}
template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren){
	if (!ren){
		return;
	}
	SDL_DestroyRenderer(ren);
}
template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex){
	if (!tex){
		return;
	}
	SDL_DestroyTexture(tex);
}
template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surf){
	if (!surf){
		return;
	}
	SDL_FreeSurface(surf);
}

// #endif