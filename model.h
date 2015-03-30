#ifndef _MODEL_H
#define _MODEL_H

enum Direction { SHOOT, IDLE, LEFT, RIGHT, DEAD, EDEAD };

typedef struct {
	int x;
	int y;
} Coordinate;

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
	// direction function
	void go(Direction d);
	// plane moving left and right
	void move();
    // Is the game over?
    bool gameOver();
	void AIM();
    // TODO: Put your stuff here
	Direction direction;
	Coordinate plane;
	Coordinate p1;
	Coordinate p2;
	Coordinate p3;
	Coordinate eplane;
private:
};

#endif