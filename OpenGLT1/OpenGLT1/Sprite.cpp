#include "Sprite.h"
#include "texTGA.h"

void Sprite::Init(float xPos, float yPos, GLdouble width, GLdouble height)
{
    m_Position.x = xPos; m_Position.y = yPos;
	m_sHeight = height /2;
	m_sWidth = width /2;

	m_TopLeft.x	= 0;
	m_TopLeft.y = height;
	m_BottomLeft.x = 0;
	m_BottomLeft.y = 0;
	m_TopRight.x = width;
	m_TopRight.y = height;
	m_BottomRight.x = width;
	m_BottomRight.y = 0;
    
    x1 = (m_Position.x - m_sWidth) + m_sWidth;
    y1 = (m_Position.y - m_sHeight) + m_sHeight;
    x2 = (m_Position.x + m_sWidth) + m_sWidth;
    y2 = m_Position.y + m_sHeight + m_sHeight;
    
    printf("Sprite created @ (%f, %f)\n", m_Position.x, m_Position.y);
}

void Sprite::LoadTexture(char *path)
{
	CreateGLTexture(path, m_TexID);
}

void Sprite::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
    glBegin(GL_QUADS);
	
    glColor3f(1.0f, 1.0f, 1.0f); // Set to white to ignore other Color state changes
    /*
	glTexCoord2d(1, 1); glVertex2d(m_TopRight.x, m_TopRight.y); // Top Right
	glTexCoord2d(0, 1); glVertex2d(m_TopLeft.x, m_TopLeft.y); // Top Left
	glTexCoord2d(0, 0); glVertex2d(m_BottomLeft.x, m_BottomLeft.y); // Bottom left
	glTexCoord2d(1, 0); glVertex2d(m_BottomRight.x, m_BottomRight.y); // Bottom Right
    */
    glTexCoord2f(1,1); glVertex2f(x2,y2);
    glTexCoord2f(0,1); glVertex2f(x1,y2);
    glTexCoord2f(0,0); glVertex2f(x1, y1);
    glTexCoord2f(1,0); glVertex2f(x2, y1);
	
    glEnd();
	glDisable(GL_TEXTURE_2D);
}