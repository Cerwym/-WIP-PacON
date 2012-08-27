#ifndef _STATEENGINE_H
#define _STATEENGINE_H

#include <vector>
#include "glfw.h"
class GameState;

class StateEngine
{
public:
	void Init(const char* title, int width = 800, int height = 600, int wndFlag = GLFW_WINDOW);
	void Destroy();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvent();
	void Update();
	void Draw();

	int Running(){return isRunning;}
	void SetActive(int pRunning){ isRunning = pRunning;}
	void Quit() {isRunning = false;}

private:
	// The states on the stack
	std::vector<GameState*> states;

	int isRunning;
	double m_CurrTime, m_LastTime;
};

#endif