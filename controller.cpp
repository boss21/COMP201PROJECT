#include "controller.h"
#include <map>

using namespace std;

Controller::Controller() {
    model = new Model();
    view = new View("Plane", 1024, 768);
}

Controller::~Controller() {
    delete model;
    delete view;
}
/**
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_a] = LEFT;
    direction[SDLK_d] = RIGHT;
	direction[SDLK_SPACE] = SHOOT;

while(!model->gameOver()) {
        currentTime = SDL_GetTicks();
        // Do stuff here to animate as 
		if (currentTime > lastTime + 30) {
			model->AIM();
			lastTime = currentTime;
		}
		
		view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
					case SDLK_a:
					case SDLK_d:
					case SDLK_SPACE:
					model->go (direction[e.key.keysym.sym]);
					model->move();
					break;
					default:
					break;
                }
				break;
			case SDL_KEYUP:
				model->direction = IDLE;
				
				break;
            }
        }
    }
    // TODO: show something nice? (ONLY USEFUL WHEN GAMEOVER)
    view->show(model);
    SDL_Delay(2000);
}
