#include "glfw.h"
#include "OpenGLSys.h"
//#include "timer.h"

int active=1;		// Window Active Flag
bool fullscreen=false;	// Fullscreen Flag

// Ugly stuff
long wWidth = 800;
long wHeight = 600;
long wBits = 32;

OpenGLSys *glRender = 0;
//CHiResTimer *g_hiResTimer = 0;
double curTime, lastTime = 0;

void shutDown()
{
	delete glRender;
	//delete g_hiResTimer;
	glfwTerminate();
}

int main(void)
{
	glRender = new OpenGLSys;
	//g_hiResTimer = new CHiResTimer;

	glfwInit();
	glfwOpenWindow(wWidth, wHeight, 5, 6, 5, 8, 24, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Pete's Little App");
	glRender->Init();
	glRender->SetProjection(wWidth, wHeight);

	// Init the timer that will 'limit' the framerate and help the program deal with updates based on time rather than frames elapsed
	//g_hiResTimer->Init();

	while (active)
	{
		lastTime = glfwGetTime(); // Get the elapsed time at the beginning of the loop
		glRender->Render();
		curTime = glfwGetTime(); // Get the elapsed time after the render function
		glRender->Update(curTime - lastTime); // Then perform an update at the real time elapsed
		glfwSwapBuffers();
		lastTime = curTime; // Reset
		active = glfwGetWindowParam(GLFW_OPENED); // if the window is closed, active is false, else true.
	}

	shutDown();
	return 0; // Won't be reached
}