#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Texture.h"
#include "Rectangle.h"
#include "SmartPtr.h"

class Image;

// Typedef of a CImage class that is wrapped inside a smart 
// pointer. 
typedef CSmartPtr<Image> TImagePtr;

// An image is manipulated directly by the end user (instead of 
// the texture). The main difference between an image and a texture
// is that the texture can contain multiple images (it is the 
// complete file). 
class Image
{
public:
	// Blit the image at the specified location
	void BlitImage(int iXOffset=0, int iYOffset=0) const;
	// Returns the texture that this image is using. 
	Texture* GetTexture() const  { return m_pTexture; }

	// Helper functions to create an new image. A smart pointer 
	// holding the new image is returned. strFileName is the 
	// name of the file containing the texture and textCoord is 
	// the rectangle in this texture which contains the image.
	static TImagePtr CreateImage(const std::string& strFileName);
	static TImagePtr CreateImage(const std::string& strFileName, 
		const TRectanglei& textCoord);

	~Image();

protected:
	// Protected constructors to avoid to be able to create a 
	// CImage instance directly. 
	Image(const std::string& strFileName);
	Image(const std::string& strFileName, const TRectanglei& textCoord);

private:
	// The texture from which this image is part of.
	Texture*   m_pTexture;
	// The rectangle that specifies the position of the image 
	// in the full texture.
	TRectanglei  m_rectTextCoord;
};

#endif  // _IMAGE_H_