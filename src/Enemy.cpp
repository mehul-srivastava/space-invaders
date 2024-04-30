#include <algorithm>
#include <ncurses.h>
#include <cstring>

#include "Enemy.h"
#include "Board.h"
#include "../exports/Exports.h"

Enemy::Enemy(int xPosition, int yPosition): Sprite(xPosition, yPosition) { //  Initializes the enemy object by calling the constructor of the sprite base class with the given position.
  value = 100;
  health = 100;// health is set to 100
  stpcpy(rep, ENEMY_REP);
  color = COLOR_GREEN;
  velocity = 1;//velocity of enemy is set to 1.
}

Enemy::Enemy(int xPosition, int yPosition, int v): Sprite(xPosition, yPosition){ 
  value = 100;
  health = 100;
  stpcpy(rep, ENEMY_REP);
  color = COLOR_GREEN;
  velocity = v;//velocity of enemy is set to v
}

Enemy::~Enemy() {}

int Enemy::getValue() {//Returns value of Value variable.
  return value;
}

int Enemy::getHealth() {// Returns value of health variable.
  return health;
}

int Enemy::takeDamage(int damage) { // The member function of Enemy class that takes damage as parameter and reduces health by damage.
  health = std::max(health - damage, 0);// Ensures that health does not go below 0.
  return health;// Returns updated health value.
}

Enemy::Board_Details Enemy::getBoardData() { //Creates a board object and retrieves the terminal height and width from the Board object and returns Board_Details struct containing terminal height and width.
  Board board;
  Board_Details details = { board.getTerminalHeight(), board.getTerminalWidth() };
  return details;
}

void Enemy::update() {// Updates Enemy's color based on its health.
  if (health <= 33) {
    color = COLOR_RED;
  } else if (health <= 66) {
    color = COLOR_MAGENTA;
  }
  setPos(position[0] - (0.05 + 0.02 * velocity), position[1]);// Updates position of the enemy.
}


void Enemy::detectCollision(Sprite& object) {
  if (object.getRep() == std::string(MISSILE_REP)) {// Takes a reference to a sprite object as a parameter and checks if the object's representation is equal to representation of missile. If so, enemy takes damage of 34.
    if (takeDamage(34) == 0) {
      Board::score++;
      destroy();// Enemy is destroyed when its health becomes 0.
    }
    object.destroy();
  }
}
