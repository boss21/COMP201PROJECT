#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
	plane.x = 487;
	plane.y = 718;
	direction = SHOOT; //not moving
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}
bool Model::gameOver() {
    return false;
}

void Model::go(Direction d) {
	direction = d;
}
//move left and right
void Model::move() {
	switch(direction) {
		case LEFT: plane.x = plane.x - 50; break;
		case RIGHT: plane.x = plane.x + 50; break;
		case SHOOT: break;
	}
}