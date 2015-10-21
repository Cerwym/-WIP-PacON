#include <stdio.h>
#include <cmath>
#include <iostream>
#include "glfw.h"
#include "StateEngine.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Windows.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

MainMenuState MainMenuState::m_MainMState;

void DebugOutput(WCHAR* szFormat, ...);
bool checkPosition(Vector2 pos);

void MainMenuState::Init()
{
	glfwSetWindowTitle("Main Menu");
	m_MenuValue = 1;
	printf("MainMenuState initialized\n");
	heroSprite.Init(13*16, 17*16, 16, 16);

#ifdef __APPLE__
	heroSprite.LoadTexture("/Users/peterlockett/Dropbox/Projects/2DOpGL/OpenGLT1/OpenGLT1/Data/Textures/soldier_2.tga");
#elif _WIN32 || _WIN64
	heroSprite.LoadTexture("Data\\Textures\\soldier_2.tga");
#endif

	// Initialize the map and collision data
	m_Map = new Map();

	if (m_Map->InitWithFile("Data/Levels/level1.txt"))
		DebugOutput(L"Level created!\n");
	else
		DebugOutput(L"Level Failed!\n");
}

void MainMenuState::Destroy()
{
	for (int x = 0; x < 28; x++)
	{
		for (int y = 0; y < 36; y++)
		{
			if (Level[x][y] != NULL)
				delete Level[x][y];
		}
	}

	delete m_Map;
	m_Map = 0;
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

}

void MainMenuState::Update(StateEngine* state, double dt)
{
	Vector2 newPos = heroSprite.Position;
	if (glfwGetKey(GLFW_KEY_ESC))
	{
		glfwTerminate();
	}

	if (glfwGetKey(GLFW_KEY_UP))
	{
		newPos.y += 64 * dt;
	}

	if ( glfwGetKey(GLFW_KEY_DOWN))
	{
		newPos.y -= 64 * dt;
	}
	if (glfwGetKey(GLFW_KEY_LEFT))
	{
		newPos.x -= 64 * dt;
	}

	if (glfwGetKey(GLFW_KEY_RIGHT) )
	{
		newPos.x += 64 * dt;
	}

	if (checkPosition(newPos))
	{
		heroSprite.Position = newPos;
	}
}

// A Unit should be considered in a cell if its centre point is in .0 - .49 of a given coordinate, or else it has begun to transition into the next.
// this function (for now) will test the player's position.
bool MainMenuState::checkPosition(Vector2 pos)
{
	// checking an element DOWN doesn't work correctly, should therefore use FLOOR insteaf of ceil.
	// this would also be the case for LEFT
	float heroCellX = pos.x / 16;
	float heroCellY = pos.y / 16;
	int x; int y;

	// RIGHT
	if (pos.x > heroSprite.Position.x)
		x = ceil(heroCellX);
	else
		x = floor(heroCellX);

	if (pos.y > heroSprite.Position.y)
		y = ceil(heroCellY);
	else
		y = floor(heroCellY);

	int cellInfo = m_Map->CheckCollision(x, y);
	if (cellInfo == 0)
	{
		return true;
	}
	else if (cellInfo == 1)
	{
		DebugOutput(L"Ate a pill!\n");
		// remove it;
		return true;
	}
	else if (cellInfo == 2)
	{
		DebugOutput(L"Hit a wall!\n");
		return false;
	}

	return false;
}

void MainMenuState::Draw(StateEngine* state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)
	glLoadIdentity(); // Reset modelview matrix

	//3D drawing here

	// Enable 2D mode
	state->m_glRender->Enable2D();

	m_Map->Draw();

	heroSprite.Draw();

	state->m_glRender->Disable2D();
}

void DebugOutput(WCHAR* szFormat, ...)
{
	WCHAR szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnwprintf(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugStringW(szBuff);
}
