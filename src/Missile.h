#ifndef missile_h
#define missile_h

#include "Sprite.h"

class Missile: public Sprite {
private:
    int power;
    bool friendly;

public:
    Missile(bool alignment);
    Missile(bool alignment, int x, int y);
    ~Missile();
    void update() override;
};

#endif