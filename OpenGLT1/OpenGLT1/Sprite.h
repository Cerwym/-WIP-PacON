#ifndef _SPRITE_H
#define _SPRITE_H

#include "glfw.h"
#include "defs.h"

class Sprite
{
public:
	void Init(float, float, GLdouble, GLdouble);
	void LoadTexture(char *path);
	void Draw();

protected:
    Vector2 m_Position;
private:
	GLuint m_TexID;
	GLdouble m_sWidth, m_sHeight;
    Vector2 m_TopLeft, m_BottomLeft, m_TopRight, m_BottomRight; // Texture coordinates, and should not be changed directly
    float x1,x2,y1,y2;
};
#endif