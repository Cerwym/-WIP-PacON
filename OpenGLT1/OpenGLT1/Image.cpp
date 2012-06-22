#include "Image.h"
#include "Exception.h"
#include "TextureManager.h"

using namespace std;

Image::Image(const string& strFileName) 
	: m_pTexture(NULL), m_rectTextCoord()
{
	// This line will throw an exception if the texture is not found. 
	m_pTexture = TextureManager::GetInstance()->GetTexture(strFileName); 
	m_pTexture->AddReference();

	// Set the texture coordinate to the full texture
	m_rectTextCoord.m_Top = m_rectTextCoord.m_Left = 0;
	m_rectTextCoord.m_Bottom = m_pTexture->GetHeight();
	m_rectTextCoord.m_Right = m_pTexture->GetWidth();
}

Image::Image(const string& strFileName, const TRectanglei& textCoord)
	: m_pTexture(NULL), m_rectTextCoord(textCoord)
{
	// This line will throw an exception if the texture is not found. 
	m_pTexture = TextureManager::GetInstance()->GetTexture(strFileName); 
	m_pTexture->AddReference();
}

TImagePtr Image::CreateImage(const string& strFileName)
{
	TImagePtr imgPtr(new Image(strFileName));
	return imgPtr;
}

TImagePtr Image::CreateImage(const string& strFileName, const TRectanglei& textCoord)
{
	TImagePtr imgPtr(new Image(strFileName,textCoord));
	return imgPtr;
}


Image::~Image()
{
	if (m_pTexture)
		m_pTexture->ReleaseReference();
}

void Image::BlitImage(int iXOffset, int iYOffset) const
{
	if (m_pTexture)
	{
		m_pTexture->Bind();

		// Get the coordinates of the image in the texture, expressed
		// as a value from 0 to 1.
		float Top	 = ((float)m_rectTextCoord.m_Top)/m_pTexture->GetHeight();
		float Bottom = ((float)m_rectTextCoord.m_Bottom)/m_pTexture->GetHeight();
		float Left   = ((float)m_rectTextCoord.m_Left)/m_pTexture->GetWidth();
		float Right  = ((float)m_rectTextCoord.m_Right)/m_pTexture->GetWidth();

		// Draw the textured rectangle.
		glBegin(GL_QUADS);
		glTexCoord2f(Left,Top);		glVertex3i(iXOffset,iYOffset,0);
		glTexCoord2f(Left,Bottom);	glVertex3i(iXOffset,iYOffset+m_rectTextCoord.GetHeight(),0);
		glTexCoord2f(Right,Bottom);	glVertex3i(iXOffset+m_rectTextCoord.GetWidth(),iYOffset+m_rectTextCoord.GetHeight(),0);
		glTexCoord2f(Right,Top);	glVertex3i(iXOffset+m_rectTextCoord.GetWidth(),iYOffset,0);
		glEnd();
	}
}


