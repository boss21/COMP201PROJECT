#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
	plane.x = 487;
	plane.y = 718;
	srand(time(0));
	eplane.x = (rand() % 50) * 19 + 21;
	eplane.y = 0;
	direction = IDLE; //not moving
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}
bool Model::gameOver() {
    return (direction == DEAD);
}
void Model::go(Direction d) {
	direction = d;
}
//move left and right
void Model::move() {
	switch(direction) {
		case LEFT: 
		if (plane.x > 30)
		plane.x -= 4;
		break;
		case RIGHT:
        if (plane.x < 944)
		plane.x += 4;
		break;
		case SHOOT: break;
		
		case IDLE: break;
	}
}
void Model::AIM() {
	if (eplane.y < 768) // maybe change to 718
	{
			eplane.y ++;
	}
}