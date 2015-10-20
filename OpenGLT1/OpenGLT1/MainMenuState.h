#ifndef _MAINMENUSTATE_H
#define _MAINMENUSTATE_H

#define MAP_X 26
#define MAP_Y 34

#include "GameState.h"
#include "Sprite.h"

#include <Vector>

using namespace std;

class MainMenuState: public GameState
{
public:
void Init();
void Destroy();

void Pause();
void Resume();

void HandleEvent(StateEngine* state);
void Update(StateEngine* state, double dt);
void Draw(StateEngine* state);

static MainMenuState* Instance()
{
	return &m_MainMState;
}

protected:
	MainMenuState(){}

private:
	static MainMenuState m_MainMState;
	int m_MenuValue;

	Sprite heroSprite;
    Sprite spriteArray[10];

	Sprite* Level[28][36];
};

#endif