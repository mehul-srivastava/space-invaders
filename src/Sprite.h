#ifndef sprite_h
#define sprite_h

#include <ncurses.h>// Include the ncurses library for terminal-based graphics
#include <string>// Include the string library for using the string data type

using namespace std;

class Sprite {
protected:
  float* position;// Pointer to a float array representing the position of the sprite
  int velocity;// Integer representing the velocity of the sprite
  bool isDestroyed; // Boolean flag indicating whether the sprite is destroyed or not
  char rep[40]; // Character array representing the visual representation of the sprite
  int color = COLOR_WHITE;// Integer representing the color of the sprite (using ncurses color constants)

public:
  Sprite();// Default constructor for the Sprite class
  Sprite(float x, float y);// Constructor for the Sprite class with parameters
  virtual ~Sprite();// Destructor for the Sprite class
  float* getPos(); // Getter function for the position array
  int getColor();// Getter function for the color
  int getVelocity(); // Getter function for the velocity
  void setPos(float x, float y);// Setter function for the position array
  int getPosX();// Getter function for the x-coordinate of the position
  int getPosY();// Getter function for the y-coordinate of the position
  char* getRep();// Getter function for the character representation
  void destroy(); // Function to mark the sprite as destroyed
  bool getIsDestroyed();// Getter function for the isDestroyed flag
  virtual void update() = 0;// Pure virtual function to update the sprite (to be implemented in derived classes)
  virtual void detectCollision(Sprite& object);// Function to detect collision with another sprite
};

#endif
