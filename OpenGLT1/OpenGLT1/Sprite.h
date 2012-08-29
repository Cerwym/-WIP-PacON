#ifndef _SPRITE_H
#define _SPRITE_H

#include "glfw.h"

class Sprite
{
public:
	Sprite::Sprite();
	Sprite::~Sprite();

	void Init(GLdouble width, GLdouble height);
	void LoadTexture(char *path, GLuint &TexID);
	void Draw();

protected:

	float m_xPos, m_yPos;
	struct Vector2
	{
		float x, y;
	}m_TopLeft, m_BottomLeft, m_TopRight, m_BottomRight;
private:

	GLuint m_TexID;
	GLdouble m_sWidth, m_sHeight;
};
#endif