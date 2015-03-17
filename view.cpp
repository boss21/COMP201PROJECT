#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }
    // Load assets
//    snake = load("assets/snake.png");
//    music = Mix_LoadMUS("assets/2Inventions_-_Johaness_Gilther_-_Don_t_leave_me.mp3");
//    if (music != NULL) {
//       Mix_PlayMusic( music, -1 );
//    }
//    food = Mix_LoadWAV("assets/yummy.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 28 );

}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    // Probably call SDL_FillRect or SDL_BlitSurface a bunch here :-)

    SDL_UpdateWindowSurface(window);
}
