#ifndef _SPRITE_H
#define _SPRITE_H

#include <glfw3.h>
#include "defs.h"

class Sprite
{
	public:
		Sprite(float xPosition, float yPosition, GLdouble width, GLdouble height);

		void LoadTexture(char *path);
		void Draw();
		void Update();
		Vector2 GetPosition(){ return m_Position; }
		void SetPosition(Vector2& pos) { m_Position = pos; }

	protected:
		GLdouble m_sWidth, m_sHeight;
		GLuint m_TexID;
		Vector2 m_TopLeft, m_BottomLeft, m_TopRight, m_BottomRight; // Texture coordinates, and should not be changed directly
		Vector2 m_Position;
		float x1, x2, y1, y2;
	private:
};
#endif