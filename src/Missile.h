#ifndef missile_h
#define missile_h

#include "Sprite.h"// Include the header file for the base Sprite class

class Missile: public Sprite {
private:
    int power; // Integer representing the power of the missile
    bool friendly; // Boolean flag indicating whether the missile is friendly or not

public:
    Missile(bool alignment);// Constructor for the Missile class with alignment parameter
    Missile(bool alignment, int x, int y);// Constructor for the Missile class with alignment and position parameters
    ~Missile();// Destructor for the Missile class
    void update() override;// Override the update function from the base Sprite class
};

#endif
