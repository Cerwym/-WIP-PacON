#ifndef _INTROSTATE_H
#define _INTROSTATE_H

#include "GameState.h"
#include "Sprite.h"

class IntroState : public GameState
{
public:
	void Init();
	void Destroy();

	void Pause();
	void Resume();

	void HandleEvent(StateEngine* state);
	void Update(StateEngine* state, double dt);
	void Draw(StateEngine* state);

	static IntroState* Instance()
	{
		return &m_IntroState;
	}

protected:
	IntroState(){} // When called, the state MUST call its own Init() function.

private:
	static IntroState m_IntroState;
	float m_rotation;

	// Sprite Stuff
	Sprite* introSprite;
};

#endif