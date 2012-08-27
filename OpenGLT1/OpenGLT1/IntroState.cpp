#include <stdio.h>

#include "StateEngine.h"
#include "GameState.h"
#include "IntroState.h"

IntroState IntroState::m_IntroState;

void IntroState::Init()
{
	printf("IntroState initialized\n");
}

void IntroState::Destroy()
{
	printf("IntroState Destroyed\n");
}

void IntroState::Pause()
{

}

void IntroState::Resume()
{

}

void IntroState::HandleEvent(StateEngine* state)
{

}

void IntroState::Update(StateEngine* state, double dt)
{

}

void IntroState::Draw(StateEngine* state)
{

}
