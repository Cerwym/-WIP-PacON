#ifndef _MAINMENUSTATE_H
#define _MAINMENUSTATE_H

#include "GameState.h"
#include "Sprite.h"

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
	float m_rotation;
	int m_MenuValue;

	Sprite heroSprite;
};

#endif