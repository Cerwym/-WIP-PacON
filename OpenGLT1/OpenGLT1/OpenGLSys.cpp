#include <windows.h> // I Severely doubt it'll make cross-platform, but whatever
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "OpenGLSys.h"

OpenGLSys::OpenGLSys(){}

OpenGLSys::~OpenGLSys(){}

bool OpenGLSys::Init()
{
	// Clear to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enabled Depth Testing
	glDepthFunc(GL_LEQUAL); // Lessens Z-Depth Fighting
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	m_rotation = 0.0f;

	return true;
}

bool OpenGLSys::Shutdown()
{
	return true;
}

void OpenGLSys::SetProjection(int width, int height)
{
	if (height == 0) // Provide divide by zero
	{
		height = 1; // By restricting height to 1
	}

	glViewport(0, 0, width, height); // Reset viewport to new dimensions
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate aspect ratio
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 600.0f);

	glMatrixMode(GL_MODELVIEW); // set modelview matrix
	glLoadIdentity(); // And reset it

	m_windowWidth = width;
	m_windowHeight = height;
}

void OpenGLSys::Update(float dt)
{
	m_rotation += dt * 50;
}

void OpenGLSys::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)
	glLoadIdentity(); // Reset modelview matrix

	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(m_rotation, 1.0f, 0.5f, 0.0f); // Rotate the cube on the X and Y axis

	glBegin(GL_QUADS);
		// TOP
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f( 1.0f, 1.0f,-1.0f); // Top Right
		glVertex3f(-1.0f, 1.0f,-1.0f); // Top Left
		glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left
		glVertex3f( 1.0f, 1.0f, 1.0f); // Bottom Right
		// Bottom
		glColor3f(1.0f, 0.5f, 0.0f); // Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		// Front
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		// Back
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		// Left
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		// Right
		glColor3f(1.0f, 0.0f, 1.0f); // Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
	glEnd();
}