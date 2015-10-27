#include "Sprite.h"
#include "texTGA.h"
#include "TexManager.h"

void Sprite::Init(float xPos, float yPos, GLdouble width, GLdouble height)
{
    Position.x = xPos; Position.y = yPos;
	m_sHeight = height /2;
	m_sWidth = width /2;
    
    printf("Sprite created @ (%f, %f) and Texture @ %p\n", Position.x, Position.y, &m_TexID);
}

void Sprite::LoadTexture(char *path)
{
	CreateGLTexture(path, m_TexID);
}

void Sprite::Draw()
{
    // Calculate new sprite vertex position
    x1 = (Position.x - m_sWidth) + m_sWidth;
    y1 = (Position.y - m_sHeight) + m_sHeight;
    x2 = (Position.x + m_sWidth) + m_sWidth;
    y2 = Position.y + m_sHeight + m_sHeight;
    
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