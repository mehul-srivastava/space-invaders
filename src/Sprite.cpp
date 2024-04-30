#include "Sprite.h"// Include the header file for the Sprite class
#include <cmath>// Include the cmath library for the floor function

Sprite::Sprite() {
   // Default constructor for the Sprite class
  // Allocates memory for the position array and initializes it with default values
  
  position = new float[2];
  position[0] = 1.0;
  position[1] = 1.0;
}

Sprite::Sprite(float x, float y) {
  // Constructor for the Sprite class with parameters
  // Allocates memory for the position array and initializes it with the given values
  position = new float[2];
  position[0] = x;
  position[1] = y;
}

Sprite::~Sprite() {
  // Destructor for the Sprite class
  // Deallocates the memory allocated for the position array
  delete[] position;
}

float* Sprite::getPos() {
  // Getter function for the position array
  return position;
}

int Sprite::getColor() {
  // Getter function for the color
  return color;
}

int Sprite::getVelocity() {
  // Getter function for the velocity
  return velocity;
}

void Sprite::setPos(float x, float y) {
  // Setter function for the position array
  // Updates the values of the position array with the given x and y coordinates
  position[0] = x;
  position[1] = y;
}

int Sprite::getPosX() {
  // Getter function for the x-coordinate of the position
  // Returns the floor value of the x-coordinate
  return (int)floor(position[0]);
}

int Sprite::getPosY() {
  // Getter function for the y-coordinate of the position
  // Returns the floor value of the y-coordinate
  return (int)floor(position[1]);
}

char* Sprite::getRep() {
  // Getter function for the character representation (rep)
  return rep;
}

void Sprite::destroy() {
  // Marks the sprite as destroyed
  isDestroyed = true;
}

bool Sprite::getIsDestroyed() {
  // Getter function for the isDestroyed flag
  return isDestroyed;
}

void Sprite::detectCollision(Sprite& object) {}// Function to detect collision with another sprite 
