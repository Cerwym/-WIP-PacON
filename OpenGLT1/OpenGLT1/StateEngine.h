#ifndef _STATEENGINE_H
#define _STATEENGINE_H

#include <vector>
#include <glfw3.h>
#include "OpenGLSys.h"
#include "TexManager.h"

class GameState;

class StateEngine
{
public:
	void Init(const char* title, int width = 800, int height = 600);
	void Destroy();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	GLFWwindow* GetGLFWWindow() const
	{ return m_Window; }

	void HandleEvent();
	void Update();
	void Draw();

	int Running() const
	{return isRunning;}

	void SetActive(int pRunning){ isRunning = pRunning;}
	void Quit() {isRunning = false;}

	void PollWindowEvent();
	
	OpenGLSys *m_glRender;
    TexManager *texManager;

protected:
		
private:
	// The states on the stack
	std::vector<GameState*> states;

	GLFWwindow* m_Window;

	int isRunning;
	double m_CurrTime, m_LastTime;
};

#endif