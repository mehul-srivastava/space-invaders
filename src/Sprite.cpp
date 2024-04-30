#include "Sprite.h"
#include <cmath>

Sprite::Sprite() {
  position = new float[2];
  position[0] = 1.0;
  position[1] = 1.0;
}

Sprite::Sprite(float x, float y) {
  position = new float[2];
  position[0] = x;
  position[1] = y;
}

Sprite::~Sprite() {
  delete[] position;
}

float* Sprite::getPos() {
  return position;
}

int Sprite::getColor() {
  return color;
}

int Sprite::getVelocity() {
  return velocity;
}

void Sprite::setPos(float x, float y) {
  position[0] = x;
  position[1] = y;
}

int Sprite::getPosX() {
  return (int)floor(position[0]);
}

int Sprite::getPosY() {
  return (int)floor(position[1]);
}

char* Sprite::getRep() {
  return rep;
}

void Sprite::destroy() {
  isDestroyed = true;
}

bool Sprite::getIsDestroyed() {
  return isDestroyed;
}

void Sprite::detectCollision(Sprite& object) {}
