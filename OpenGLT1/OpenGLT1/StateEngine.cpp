#include <stdio.h>

#include "glfw.h"
#include "StateEngine.h"
#include "GameState.h"

void StateEngine::Init(const char* title, int width, int height, int wndFlag)
{
	glfwInit();
	glfwOpenWindow(width, height, 5, 6, 5, 8, 24, 0, wndFlag);
	glfwSetWindowTitle(title);

	isRunning = true;
	
	m_glRender = new OpenGLSys;
	// Every state is an OpenGL window so it makes sense to init the render space
	m_glRender->Init();
	m_glRender->SetProjection(width, height); // And then set the projection

	printf("Engine Initialized\n");
}

void StateEngine::Destroy()
{
	// Cleanup the states on the stack
	while (!states.empty())
	{
		states.back()->Destroy();
		states.pop_back();
	}

	printf("Engine cleaned up\n");

	delete m_glRender;
	glfwTerminate();
}

void StateEngine::ChangeState(GameState* state)
{
	// Destroy the CURRENT state
	if (!states.empty())
	{
		states.back()->Destroy();
		states.pop_back();
	}

	// Store and init the new state, fresh to the party
	states.push_back(state);
	states.back()->Init();
}

void StateEngine::PushState(GameState* state)
{
	// 'Pause' the current state
	if (!states.empty())	{states.back()->Pause();}

	// Store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void StateEngine::PopState()
{
	// DESTROY the current state
	if (!states.empty())
	{
		states.back()->Destroy();
		states.pop_back();
	}

	// Resume the previous state
	if (!states.empty())	{states.back()->Resume();}
}

void StateEngine::HandleEvent()
{
	states.back()->HandleEvent(this);
}

void StateEngine::Update()
{
	m_LastTime = glfwGetTime();
	states.back()->Update(this, m_CurrTime - m_LastTime);
	m_LastTime = m_CurrTime;
}

void StateEngine::Draw()
{
	m_CurrTime = glfwGetTime();
	states.back()->Draw(this);
	glfwSwapBuffers();
}