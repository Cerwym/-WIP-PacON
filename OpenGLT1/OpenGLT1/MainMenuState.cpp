#include <stdio.h>
#include "glfw.h"
#include "StateEngine.h"
#include "GameState.h"
#include "MainMenuState.h"

MainMenuState MainMenuState::m_MainMState;

void MainMenuState::Init()
{
	glfwSetWindowTitle("Main Menu");
	m_MenuValue = 1;
	printf("MainMenuState initialized\n");
	heroSprite.Init(400,300,32,32);
    
#ifdef __APPLE__
    heroSprite.LoadTexture("/Users/peterlockett/Dropbox/Projects/2DOpGL/OpenGLT1/OpenGLT1/Data/Textures/soldier_2.tga");
#elif _WIN32 || _WIN64
	heroSprite.LoadTexture("Data\\Textures\\soldier_2.tga");
#endif
}

void MainMenuState::Destroy()
{
	printf("MainMenuState Destroyed\n");
}

void MainMenuState::Pause()
{

}

void MainMenuState::Resume()
{

}

void MainMenuState::HandleEvent(StateEngine* state)
{
	if (glfwGetKey(GLFW_KEY_ESC))
	{
		glfwTerminate();
	}
	
	if (glfwGetKey(GLFW_KEY_UP))
	{
		m_MenuValue -=1;
		if (m_MenuValue = 0){m_MenuValue = 3;}
	}
	if(glfwGetKey(GLFW_KEY_DOWN))
	{
		m_MenuValue +=1;
		if(m_MenuValue = 4){m_MenuValue = 1;}
	}
}

void MainMenuState::Update(StateEngine* state, double dt)
{
	m_rotation += dt * 50;
}

void MainMenuState::Draw(StateEngine* state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)
	glLoadIdentity(); // Reset modelview matrix

	//3D drawing here
	state->m_glRender->Enable2D();

	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);
	glVertex2d(0, 0);
	glColor3ub(0, 255, 0);
	glVertex2d(100, 0);
	glColor3ub(0, 0, 255);
	glVertex2d(50, 50);
	glEnd();

	heroSprite.Draw();

	state->m_glRender->Disable2D();
}
