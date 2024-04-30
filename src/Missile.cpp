#include "Missile.h"// Include the header file for the Missile class
#include "../exports/Exports.h"// Include the header file for the exported constants

#include <cstring>// Include the cstring library for string operations

Missile::Missile(bool alignment): power(1), friendly(alignment) {
 // Constructor for the Missile class with alignment parameter
  // Initializes the power and friendly member variables
  // Copies the missile representation constant to the rep variable
 stpcpy(rep, MISSILE_REP);
}

Missile::Missile(bool alignment, int xPosition, int yPosition): Sprite(xPosition, yPosition), power(1), friendly(alignment) {
 // Constructor for the Missile class with alignment and position parameters
  // Calls the base class (Sprite) constructor with the provided x and y positions
  // Initializes the power and friendly member variables
  // Copies the missile representation constant to the rep variable
  stpcpy(rep, MISSILE_REP);
}
Missile::~Missile() {}

void Missile::update() {
  // Implementation of the update function from the base class
  // Updates the position of the missile by incrementing the x-coordinate by 1
  setPos(getPosX() + 1, getPosY());
}
