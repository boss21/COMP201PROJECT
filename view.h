#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "model.h"
#include <map>
#include <string>

#ifndef _VIEW_H
#define _VIEW_H

// Show (output) the state of the model
class View {
public:
    View(std::string title, int width, int height);
    ~View();
    // Print out the visible stuff in the grid
    void show(Model * model);
private:
    SDL_Window* window;
    SDL_Surface* screen;
    bool fail;
    SDL_Surface* load(char * path);
	SDL_Surface* cloud;
	SDL_Surface* plane[2];
	SDL_Surface* eplane[4];
	SDL_Surface* p[3];
	int phase;
	int dmg;
//    SDL_Surface* text;
    Mix_Music * music;
    Mix_Chunk * bullet;
	Mix_Chunk * explos;
    TTF_Font * font;
};
#endif