#include <stdio.h>
#include <iostream>
#include "glfw.h"
#include "StateEngine.h"
#include "GameState.h"
#include "MainMenuState.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

MainMenuState MainMenuState::m_MainMState;

void MainMenuState::Init()
{
	glfwSetWindowTitle("Main Menu");
	m_MenuValue = 1;
	printf("MainMenuState initialized\n");
	heroSprite.Init(432, 560, 16, 16);
    
#ifdef __APPLE__
    heroSprite.LoadTexture("/Users/peterlockett/Dropbox/Projects/2DOpGL/OpenGLT1/OpenGLT1/Data/Textures/soldier_2.tga");
#elif _WIN32 || _WIN64
	heroSprite.LoadTexture("Data\\Textures\\soldier_2.tga");
#endif
    
	/*
    //do the array
    for (int i = 0; i < 10; i ++)
    {
        spriteArray[i].Init(16*i, 16 * i, 16, 16);
#ifdef __APPLE__
		spriteArray[i].LoadTexture("/Users/peterlockett/Dropbox/Projects/2DOpGL/OpenGLT1/OpenGLT1/Data/Textures/soldier_2.tga");
#elif _WIN32 || _WIN64
		spriteArray[i].LoadTexture("Data\\Textures\\soldier_2.tga");
#endif
    }

	*/

	// Initialize the map
	for (int x = 0; x < 29; x++)
	{
		for (int y = 0; y < 36; y++)
		{
			srand(time(NULL));
			int v = rand() % 3;
			if (v != 1)
			{
				Sprite* tSprite = new Sprite;
				tSprite->Init(16 * x, 16 * y, 16, 16);
				tSprite->LoadTexture("Data\\Textures\\pill.tga");
				Level[x][y] = tSprite;
			}

			else
			{
				Level[x][y] = NULL;
			}
		}
	}

	delete Level[10][10];
	Level[10][10] = 0;
}

void MainMenuState::Destroy()
{
	for (int x = 0; x < 29; x++)
	{
		for (int y = 0; y < 36; y++)
		{
			delete Level[x][y];
		}
	}
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
	bool isKeyDown = false;
	if (glfwGetKey(GLFW_KEY_ESC))
	{
		glfwTerminate();
	}

	if (glfwGetKey(GLFW_KEY_UP))
	{
		isKeyDown = true;
		heroSprite.Position.y += 64 * dt;
	}

	if ( glfwGetKey(GLFW_KEY_DOWN) && !isKeyDown)
	{
		isKeyDown = true;
		heroSprite.Position.y -= 64 * dt;
	}
	if (glfwGetKey(GLFW_KEY_LEFT) && !isKeyDown)
	{
		isKeyDown = true;
		heroSprite.Position.x -= 64 * dt;
	}

	if (glfwGetKey(GLFW_KEY_RIGHT) && !isKeyDown)
	{
		isKeyDown = true;
		heroSprite.Position.x += 64 * dt;
	}
}

void MainMenuState::Draw(StateEngine* state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)
	glLoadIdentity(); // Reset modelview matrix

	//3D drawing here
	state->m_glRender->Enable2D();

	for (int y = 0; y < 36; y++)
		for (int x = 0; x < 29; x++)
			if (Level[x][y] != NULL)
				Level[x][y]->Draw();


	heroSprite.Draw();

	state->m_glRender->Disable2D();
}
