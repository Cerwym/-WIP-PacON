#include "glfw.h"
#include "StateEngine.h"
#include "MainMenuState.h"
#include "W32Console.h"

StateEngine engine;

void shutDown()
{
	engine.Destroy();
}

int main(void)
{
	// if we are building under windows AND in debug mode, create a console window
	// change this so it doesn't create in release mode.
#ifdef _WIN32
	Debug::W32Console::Create(80, 25);
#endif

	// Init the manager
	engine.Init("PacON", 448,576);
	// Load the intro state
	engine.ChangeState(MainMenuState::Instance());

	while (engine.Running())
	{
		engine.HandleEvent();
		engine.Draw();
		engine.Update();
		engine.SetActive(glfwGetWindowParam(GLFW_OPENED)); // if the window is closed, active is false, else true.
	}

	shutDown();

#ifdef _WIN32
	Debug::W32Console::Destroy();
#endif
	return 0; // Won't be reached
}