#include "Player.h"

Player::Player(float xPosition, float yPosition, GLdouble width, GLdouble height)
	:Sprite(xPosition, yPosition, width, height)
{
	printf("this one was a player sprite!\n");
}