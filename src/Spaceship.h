#ifndef spaceship_h
#define spaceship_h

#include <ctime>
#include "Sprite.h"
#include "../exports/Exports.h"
// This is the spaceship class header file that is used to handle the spaceship object and all its attributes
class Spaceship : public Sprite // inheritance from the Sprite class
{
private:
  int lives; // this stores the number of lives left
  // there are the dimensions of the 2D space
  int board_width;  // width of the 2D space
  int board_height; // heigh of the 2D space

public:
  bool isPowerupActivated = false;   // keep track of the status of powerup Activation
  int powerups_left = POWERUPS_LEFT; // number of power ups left
  int roundDuringPowerupActivation;  // An integer to store the current round of enemies when a powerup is activated to keep the current power up valid for that round

  Spaceship();                                    // default constructor
  Spaceship(int x, int y, int width, int height); // constructor to initialise a spacehship object with the coordinates and dimensions.
  int getLives();                                 // function declaration for accessing the number of lives left
  //***the following functions are used for moving the space in the 2D space.
  void moveLeft();  // function declaration for moving to the left
  void moveRight(); // function declaration for moving to the right
  void moveUp();    // function declaration for moving up
  void moveDown();  // function declaration for moving down
  //***

  void loseLife(); // reduce life count when an alien reaches the left wall.

  void update() override; // used to update the spaceship object with its new attributes
};

#endif