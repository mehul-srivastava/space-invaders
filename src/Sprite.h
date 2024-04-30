#ifndef sprite_h
#define sprite_h

#include <ncurses.h>
#include <string>

using namespace std;

class Sprite {
protected:
  float* position;
  int velocity;
  bool isDestroyed;
  char rep[40];
  int color = COLOR_WHITE;

public:
  Sprite();
  Sprite(float x, float y);
  virtual ~Sprite();
  float* getPos();
  int getColor();
  int getVelocity();
  void setPos(float x, float y);
  int getPosX();
  int getPosY();
  char* getRep();
  void destroy();
  bool getIsDestroyed();
  virtual void update() = 0;
  virtual void detectCollision(Sprite& object);
};

#endif