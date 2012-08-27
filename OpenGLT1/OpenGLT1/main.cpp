#include "glfw.h"
#include "OpenGLSys.h"
#include "StateEngine.h"
#include "IntroState.h"

// Ugly stuff
long wWidth = 800;
long wHeight = 600;

OpenGLSys *glRender = 0;
double dt, lastTime = 0;

void shutDown()
{
	delete glRender;
}

int main(void)
{
	glRender = new OpenGLSys;
	StateEngine engine;

	// Init the manager
	engine.Init("Game");
	// Load the intro state
	engine.ChangeState(IntroState::Instance());

	glRender->Init();
	glRender->SetProjection(wWidth, wHeight);

	while (engine.Running())
	{
		engine.HandleEvent();
		engine.Draw();
		engine.Update();
		engine.SetActive(glfwGetWindowParam(GLFW_OPENED)); // if the window is closed, active is false, else true.
	}

	shutDown();
	return 0; // Won't be reached
}