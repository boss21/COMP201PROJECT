#ifndef _MODEL_H
#define _MODEL_H

enum Direction { SHOOT, LEFT, RIGHT };

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
	void go(Direction d);
	void move();
    // Is the game over?
    bool gameOver();
    // TODO: Put your stuff here
	Direction direction;
	Coordinate plane;
private:
};

#endif