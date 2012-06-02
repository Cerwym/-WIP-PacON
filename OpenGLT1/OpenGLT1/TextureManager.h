#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "Texture.h"
#include <string>
#include <map>
// This texture manager will allow a texture to be loaded once and used multiple times
// like the way a Texture2D assignment in XNA works
class TextureManager
{
public:
	// Loads a texture BY filename
	// If the texture is not already loaded, it will load and store it, then return it
	// if the texture is ALREADY loaded it simply returns the existing one
	Texture* GetTexture(const std::string& strTextName);
	// Release the texture, return true if found and released.
	bool ReleaseTexture(const std::string& strTextName);

	// Returns the single instance of the texture manager.
	// Implemented as a singleton.
	static TextureManager* GetInstance();

protected:
	TextureManager();
	~TextureManager();

private:
	typedef std::map<std::string, Texture*> TTextureMap;
	// The map of already loaded textures. They are indexed by filename
	TTextureMap m_Textures;
};
#endif