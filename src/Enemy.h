#ifndef enemy_h
#define enemy_h

#include "Sprite.h"

class Enemy: public Sprite {
private://Following member variables and functions are private and can only be accesssed within the Enemy class.
  int value;
  int health;
  int moveState;
  int moveStateTowardsSpaceshipToggle;

public://Following member variables and functions are public and can be accessed outside the Enemy class.
  struct Board_Details {//Contains the height and and width of the board.
    int height;
    int width;
  };

  Enemy(int x, int y);
  Enemy(int x, int y, int v);
  ~Enemy();
  int getValue();
  int getHealth();
  int takeDamage(int damage);
  void update() override;
  Board_Details getBoardData();
  void detectCollision(Sprite& object) override;//It takes a reference to a Sprite object as a parameter and is marked with override keyword, meaning that it overrides a virtual function in the base class.
};
#endif
