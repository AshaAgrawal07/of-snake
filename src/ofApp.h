#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "snake.h"
#include "SnakeFood.h"

namespace snakelinkedlist {

// Enum to represent the current state of the game
enum GameState {
  IN_PROGRESS = 0,
  PAUSED,
  FINISHED,
  TOP_TEN
};

//from:  https://www.quora.com/How-can-I-sort-numbers-in-descending-order-using-C++-STL
//struct greater
//{
//	template<class T>
//	bool operator()(T const &a, T const &b) const { return a > b; }
//};

class snakeGame : public ofBaseApp {
private:
	GameState current_state_ = IN_PROGRESS; // The current state of the game, used to determine possible actions
	Snake game_snake_; // The object that represents the user controlled snake
	SnakeFood game_food_; // The object that represents the food pellet the user is attempting to eat with the snake

	bool should_update_ = true;     // A flag boolean used in the update() function. Due to the frame dependent animation we've
									// written, and the relatively low framerate, a bug exists where users can prefire direction 
									// changes faster than a frame update. Our solution is to force a call to update on direction
									// changes and then not update on the next frame to prevent the snake from skipping across the screen.
							

	// Private helper methods to render various aspects of the game on screen.
	void drawFood(); 
	void drawSnake();
	void drawGameOver();
	void drawGamePaused();

	// Resets the game objects to their original state.
	void reset();

	vector<int> records; //the vector that will update when scores are added (will contain top-10)
	ofSoundPlayer soundPlayer;

public:
	
	// Function used for one time setup
	void setup();

	// Main event loop functions called on every frame
	void update();
	void draw();
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
	void windowResized(int w, int h);

	//outputs the current score as well as the top 10
	void score();

	//outputs the top 10 scores
	void top_ten();
};
} // namespace snakelinkedlist
