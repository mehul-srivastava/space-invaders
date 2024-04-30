#include "Spaceship.h"
#include "Board.h"
#include "../exports/Exports.h"
#include <cstring>
// This default constructor initializes the spaceship with a predefined number of lives (SPACESHIP_LIVES) and a representation (SPACESHIP_REP). These variables are declared in the Exports.h file
Spaceship::Spaceship()
{
  lives = SPACESHIP_LIVES;    // sets the number of lives
  stpcpy(rep, SPACESHIP_REP); // copies the spaceship visual representation to rep variable
}
// This constructor takes the initial position (x, y) and the dimensions of the game board (width, height) as arguments. It initializes the spaceship with the same default lives and representation as the default constructor, and also sets the initial position and board dimensions.
Spaceship::Spaceship(int x, int y, int width, int height)
{
  lives = SPACESHIP_LIVES;    // sets the number of lives
  stpcpy(rep, SPACESHIP_REP); // copies the spaceship visual representation to rep variable
  position[0] = x;            // sets the position on the x-axis of the board
  position[1] = y;            // sets the position on the y-axis of the board
  board_width = width;        // sets board width
  board_height = height;      // sets board height
}
// Moves the spaceship to the right by a fixed amount (10 units), unless it's too close to the right edge of the board, in which case it moves by a smaller amount (1 unit).
void Spaceship::moveRight()
{
  if (board_width - 40 - position[0] <= 20)
  {                                       // checks if the spaceships is close to the edge
    setPos(position[0] + 1, position[1]); // move the spaceship to the right by 1 unit
    return;
  }
  setPos(position[0] + 10, position[1]); // move the spaceship to the right by 10 unit
}
// Moves the spaceship to the left by a fixed amount (10 units), unless it's too close to the left edge of the board, in which case it moves by a smaller amount (1 unit).
void Spaceship::moveLeft()
{
  if (position[0] <= 10)
  {
    setPos(position[0] - 1, position[1]); // move the spaceship to the left by 1 unit
    return;
  }
  setPos(position[0] - 10, position[1]); // move the spaceship to the left by 10 unit
}
// Moves the spaceship down by 1 unit.
void Spaceship::moveDown()
{
  setPos(position[0], position[1] + 1);
}

// Moves the spaceship up by 1 unit.
void Spaceship::moveUp()
{
  setPos(position[0], position[1] - 1);
}
// Returns the current number of lives the spaceship has.
int Spaceship::getLives()
{
  return lives; // returns the number of lives left
}
// Decrements the number of lives by 1.
void Spaceship::loseLife()
{
  lives = lives - 1; // decrements the variable lives by 1
}

void Spaceship::update() {}
