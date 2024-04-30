#include "Missile.h"
#include "../exports/Exports.h"

#include <cstring>

Missile::Missile(bool alignment): power(1), friendly(alignment) {
 stpcpy(rep, MISSILE_REP);
}

Missile::Missile(bool alignment, int xPosition, int yPosition): Sprite(xPosition, yPosition), power(1), friendly(alignment) {
  stpcpy(rep, MISSILE_REP);
}

Missile::~Missile() {}

void Missile::update() {
  setPos(getPosX() + 1, getPosY());
}
