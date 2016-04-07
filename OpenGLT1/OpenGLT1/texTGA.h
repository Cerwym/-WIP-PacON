#ifndef _TEXTGA_H_
#define _TEXTGA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glfw3.h>

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;

typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

bool LoadUncompressedTGA(char * filename, FILE * fTGA);
bool LoadCompressedTGA( char * filename, FILE * fTGA);
bool CreateGLTexture(char *name, GLuint & TexID  );

#endif 