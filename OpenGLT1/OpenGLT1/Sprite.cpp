#include "Sprite.h"
#include "texTGA.h"

Sprite::Sprite(){}
Sprite::~Sprite(){}

void Sprite::Init(GLdouble width, GLdouble height)
{
	m_sHeight = height;
	m_sWidth = width;

	m_TopLeft.x	= 0;
	m_TopLeft.y = height;
	m_BottomLeft.x = 0;
	m_BottomLeft.y = 0;
	m_TopRight.x = width;
	m_TopRight.y = height;
	m_BottomRight.x = width;
	m_BottomRight.y = 0;
}

void Sprite::LoadTexture(char *path, GLuint &TexID)
{
	m_TexID = TexID;
	CreateGLTexture(path, m_TexID);
}

void Sprite::Draw()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_TexID);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 1); glVertex2d(m_TopRight.x, m_TopRight.y); // Top Right
	glTexCoord2d(0, 1); glVertex2d(m_TopLeft.x, m_TopLeft.y); // Top Left
	glTexCoord2d(0, 0); glVertex2d(m_BottomLeft.x, m_BottomLeft.y); // Bottom left
	glTexCoord2d(1, 0); glVertex2d(m_BottomRight.x, m_BottomRight.y); // Bottom Right
	glEnd();
	glDisable(GL_TEXTURE_2D);
}