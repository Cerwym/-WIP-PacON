#include "Sprite.h"
#include "texTGA.h"
#include "TexManager.h"


Sprite::Sprite(float xPosition, float yPosition, GLdouble width, GLdouble height)
{
	m_Position.x = xPosition; m_Position.y = yPosition;
	m_sHeight = height / 2;
	m_sWidth = width / 2;
	m_TexID = 0;

	printf("Sprite created @ (%f, %f)\n", m_Position.x, m_Position.y);
}

void Sprite::LoadTexture(char *path)
{
	CreateGLTexture(path, m_TexID);
}

void Sprite::Draw()
{
    // Calculate new sprite vertex position
	x1 = (m_Position.x - m_sWidth) + m_sWidth;
	y1 = (m_Position.y - m_sHeight) + m_sHeight;
	x2 = (m_Position.x + m_sWidth) + m_sWidth;
	y2 = (m_Position.y + m_sHeight) + m_sHeight;
    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
    glBegin(GL_QUADS);
	
    glColor3f(1.0f, 1.0f, 1.0f); // Set to white to ignore other Color state changes

    glTexCoord2f(1,1); glVertex2f(x2,y2);
    glTexCoord2f(0,1); glVertex2f(x1,y2);
    glTexCoord2f(0,0); glVertex2f(x1, y1);
    glTexCoord2f(1,0); glVertex2f(x2, y1);
	
    glEnd();
	glDisable(GL_TEXTURE_2D);
}