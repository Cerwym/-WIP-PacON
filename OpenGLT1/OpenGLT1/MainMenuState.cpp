#include <stdio.h>
#include <cmath>
#include <iostream>
#include <glfw3.h>
#include "StateEngine.h"
#include "GameState.h"
#include "MainMenuState.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

MainMenuState MainMenuState::m_MainMState;

bool checkPosition(Vector2 pos);

void MainMenuState::Init()
{
	m_MenuValue = 1;
	printf("MainMenuState initialized\n");

	// Initialize the map and collision data
	m_Map = new Map();

	if (m_Map->InitWithFile("Data/Levels/level1.txt"))
		printf("Level created!\n");
	else
		printf("Level Failed!\n");

	mPlayer = new Player(13 * 16, 17 * 16, 16, 16);
	mPlayer->LoadTexture("Data\\Textures\\soldier_2.tga");
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
	// rather than move the player a fixed amount per frame, check for input and move the character in that direction
	// every frame move by velocity, the input will change the velocity of the player.

	Vector2 newPos = mPlayer->GetPosition();
	if (glfwGetKey(state->GetGLFWWindow(), GLFW_KEY_ESCAPE))
	{
		glfwTerminate();
	}

	if (glfwGetKey(state->GetGLFWWindow(), GLFW_KEY_UP))
	{
		newPos.y += 64 * dt;
	}

	if ( glfwGetKey(state->GetGLFWWindow(), GLFW_KEY_DOWN))
	{
		newPos.y -= 64 * dt;
	}
	if (glfwGetKey(state->GetGLFWWindow(), GLFW_KEY_LEFT))
	{
		newPos.x -= 64 * dt;
	}

	if (glfwGetKey(state->GetGLFWWindow(), GLFW_KEY_RIGHT) )
	{
		newPos.x += 64 * dt;
	}

	if (checkPosition(newPos))
	{
		mPlayer->SetPosition(newPos);
	}
}

// A Unit should be considered in a cell if its centre point is in .0 - .49 of a given coordinate, or else it has begun to transition into the next.
// this function (for now) will test the player's position.
bool MainMenuState::checkPosition(Vector2 pos)
{
	// checking an element DOWN doesn't work correctly, should therefore use FLOOR insteaf of ceil.
	// this would also be the case for LEFT
	float heroCellX = (pos.x + 8) / 16;
	float heroCellY = (pos.y + 8) / 16;
	int x; int y;

	// RIGHT
	if (pos.x > mPlayer->GetPosition().x)
		x = ceil(heroCellX);
	else
		x = floor(heroCellX);

	if (pos.y > mPlayer->GetPosition().y)
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
		printf("Ate a pill!\n");
		// remove it;
		return true;
	}
	else if (cellInfo == 2)
	{
		printf("Hit a wall!\n");
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

	mPlayer->Draw();

	state->m_glRender->Disable2D();
}