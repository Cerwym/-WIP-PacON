#include "Sprite.h"
#include <stdio.h>

class Player : public Sprite
{
public:
	Player(float xPosition, float yPosition, GLdouble width, GLdouble height);
};