#include "glfw.h"
#include "StateEngine.h"
#include "MainMenuState.h"

StateEngine engine;

void shutDown()
{
	engine.Destroy();
}

int main(void)
{
	// Init the manager
	engine.Init("Netman", 448,576);
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
	return 0; // Won't be reached
}