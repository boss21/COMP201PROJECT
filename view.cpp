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
	cloud = load("assets/cloud.jpg");
	win = load("assets/win.jpg");
	lose = load("assets/lose.jpg");
	plane[0] = load("assets/plane.png");
	plane[1] = load("assets/plane2.png");
	p[0] = load("assets/p1.png");
	p[1] = load("assets/p2.png");
	p[2] = load("assets/p3.png");
	eplane[0] = load("assets/eplane.png");
	eplane[1] = load("assets/eplane1.png");
	eplane[2] = load("assets/eplane2.png");
	eplane[3] = load("assets/eplane3.png");
	phase = 0;
	dmg = 0;

    music = Mix_LoadMUS("assets/bground.mp3");
    if (music != NULL) {
        Mix_PlayMusic( music, -1 );
    }
    bullet = Mix_LoadWAV("assets/bullet.wav");
	explos = Mix_LoadWAV("assets/explosion.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 20 );
}

View::~View() {
	TTF_CloseFont ( font );
	TTF_Quit();
	Mix_FreeMusic(music);
	Mix_FreeChunk(bullet);
	Mix_FreeChunk(explos);
	SDL_FreeSurface(text);
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
	SDL_Rect d;
	SDL_Rect de;
	SDL_Rect des;
	SDL_Rect dest;
	SDL_Rect destn;
	SDL_Rect destnn;
	dest.x = model->plane.x;
	dest.y = model->plane.y;
	destn.x = model->plane.x;
	destn.y = model->plane.y - 50;
	destnn.x = model->eplane.x;
	destnn.y = model->eplane.y;
	if (model->direction == SHOOT) {
        Mix_PlayChannel( -1, bullet, 0 );
    }
// images
	SDL_BlitSurface( cloud, NULL, screen, NULL );
	if (model->direction != DEAD)
	{
	SDL_SetColorKey(plane[0], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
	SDL_BlitSurface( plane[0], NULL, screen, &dest );
	SDL_SetColorKey(eplane[0], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
	SDL_BlitSurface( eplane[0], NULL, screen, & destnn );
	// bullets move
	if (model->direction == SHOOT)
	{
		SDL_SetColorKey(p[phase], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
		SDL_BlitSurface(p[phase], NULL, screen, &destn );
		phase = (phase + 1) % 3;
	}
			if ((model->direction == SHOOT) && (model->eplane.x > model->plane.x - 50) && (model->eplane.x < model->plane.x + 50))
			{
			// Stupid thing wont even show the 3 phases, need to find a way to delay
			SDL_SetColorKey(eplane[dmg], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_BlitSurface(eplane[dmg], NULL, screen, &destnn );
			dmg = (dmg + 1) % 4;
			}
	}
		
		if (dmg == 1)
		{
			SDL_Delay(300);
			SDL_SetColorKey(eplane[1], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_BlitSurface(eplane[1], NULL, screen, &destnn );
			Mix_PlayChannel( -1, bullet, 0 );
		}
		if (dmg == 2)
		{
			SDL_Delay(300);
			SDL_SetColorKey(eplane[2], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_BlitSurface(eplane[2], NULL, screen, &destnn );
		}
		if (dmg == 3)
		{
			SDL_SetColorKey(eplane[3], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_BlitSurface(eplane[3], NULL, screen, &destnn );
			SDL_SetColorKey(plane[0], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_BlitSurface(plane[0], NULL, screen, &dest );
			Mix_PlayChannel( -1, explos, 0 );
			
			SDL_Color textColor = { 51, 51, 0 };
			text = TTF_RenderText_Solid( font, "[ USE A to move LEFT, D to move RIGHT, and SPACEBAR to SHOOT ]", textColor );
			de.x = 330;
			de.y = 18;
			SDL_BlitSurface( text, NULL, screen, &de );
			
			SDL_Color textColor1 = { 204, 0, 0 };
			text = TTF_RenderText_Solid( font, "SCORE: 1000", textColor1 );
			d.x = 110;
			d.y = 18;
			SDL_BlitSurface( text, NULL, screen, &d );
			
			SDL_UpdateWindowSurface(window);
			SDL_Delay(4000);
			SDL_BlitSurface( win, NULL, screen, NULL );
			model->go(DEAD);
		}
	// planes collide
	if ((model->plane.y == model->eplane.y + 50) && (model->eplane.x > model->plane.x - 50) && (model->eplane.x < model->plane.x + 50))
	{
		SDL_SetColorKey(plane[1], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
		SDL_BlitSurface(plane[1], NULL, screen, &dest );
		SDL_SetColorKey(eplane[3], SDL_TRUE, SDL_MapRGB(screen->format,0x00,0x00,0x00));
		SDL_BlitSurface(eplane[3], NULL, screen, &destnn );	
		Mix_PlayChannel( -1, explos, 0 );
		SDL_UpdateWindowSurface(window);
		SDL_Delay(500);
		SDL_BlitSurface( lose, NULL, screen, NULL );
		model->go(DEAD);
	}
	if (model->eplane.y + 50 > 768)
	{
		Mix_PlayChannel( -1, explos, 0 );
		SDL_BlitSurface( lose, NULL, screen, NULL );
		model->go(DEAD);
	}
	if (model->direction != DEAD)
	{
	SDL_Color textColor = { 51, 51, 0 };
    text = TTF_RenderText_Solid( font, "[ USE A to move LEFT, D to move RIGHT, and SPACEBAR to SHOOT ]", textColor );
    de.x = 330;
    de.y = 18;
    SDL_BlitSurface( text, NULL, screen, &de );
	
	SDL_Color textColor1 = { 204, 0, 0 };
    text = TTF_RenderText_Solid( font, "SCORE: 0", textColor1 );
    d.x = 110;
    d.y = 18;
    SDL_BlitSurface( text, NULL, screen, &d );
	}
    SDL_UpdateWindowSurface(window);
}