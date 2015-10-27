#include <stdio.h>
#include "glfw.h"
#include "StateEngine.h"
#include "GameState.h"
#include "IntroState.h"
#include "MainMenuState.h"

#include "texTGA.h" // Used for loading in a TGA and applying it as a GLtexture

IntroState IntroState::m_IntroState;

void IntroState::Init()
{
	glfwSetWindowTitle("Intro");

	introSprite = new Sprite(0, 0, 800, 600);
#ifdef __APPLE__
    printf("Hi, i'm on OSX\n");
	introSprite->LoadTexture("/Users/peterlockett/Dropbox/Projects/2DOpGL/OpenGLT1/OpenGLT1/Data/Textures/IntroTex.tga");
#elif _WIN32 || _WIN64
    introSprite->LoadTexture("Data\\Textures\\IntroTex.tga");
#endif 
	printf("IntroState initialized\n");
}

void IntroState::Destroy()
{
	printf("IntroState Destroyed\n");
	delete introSprite;
	introSprite = 0;
}

void IntroState::Pause()
{

}

void IntroState::Resume()
{

}

void IntroState::HandleEvent(StateEngine* state)
{
	if (glfwGetKey(GLFW_KEY_ENTER))
		state->ChangeState(MainMenuState::Instance());
}

void IntroState::Update(StateEngine* state, double dt)
{
	m_rotation += dt * 50;
}

void IntroState::Draw(StateEngine* state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)

	state->m_glRender->Enable2D();

	introSprite->Draw();

	state->m_glRender->Disable2D();
}
