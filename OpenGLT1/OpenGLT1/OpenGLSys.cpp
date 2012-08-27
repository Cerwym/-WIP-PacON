#include "glfw.h"
#include "OpenGLSys.h"

OpenGLSys::OpenGLSys(){}

OpenGLSys::~OpenGLSys(){}

bool OpenGLSys::Init()
{
	// Clear to black
	glShadeModel(GL_SMOOTH); // Enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enabled Depth Testing
	glDepthFunc(GL_LEQUAL); // Lessens Z-Depth Fighting
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return true;
}

bool OpenGLSys::Shutdown()
{
	return true;
}

bool OpenGLSys::SetProjection(int width, int height)
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
	
	m_windowHeight = width;
	m_windowWidth = width;
	return true;
}

void OpenGLSys::Enable2D()
{
	int vPort[4];
	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void OpenGLSys::Disable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}