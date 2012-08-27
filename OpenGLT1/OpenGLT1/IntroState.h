#ifndef _INTROSTATE_H
#define _INTROSTATE_H

#include "GameState.h"

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
	IntroState(){}

private:
	static IntroState m_IntroState;
	float m_rotation;
};

#endif