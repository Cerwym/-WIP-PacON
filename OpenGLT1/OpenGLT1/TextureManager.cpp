#include <IL/il.h>

#include "TextureManager.h"
#include "Exception.h"

using namespace std;

TextureManager::TextureManager() : m_Textures()
{
	// Init Devil
	ilInit();

	// Set the first loaded point to be upper left of the whole image
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}

TextureManager::~TextureManager()
{
	// Delete all textures from the start of the map to the end
	TTextureMap::iterator iter = m_Textures.begin();
	for (iter; iter !=m_Textures.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
	}
}
TextureManager* TextureManager::GetInstance()
{
	/*
	 * I'm implementing this as a singleton pattern to make sure there's only ever
	 * one instance of the texture (uniqueness) and gives a way to access it
	 */

	// Returns the unique class instance.
	static TextureManager Instance;
	return &Instance;
}

Texture* TextureManager::GetTexture(const string& strTextName)
{
	// Look in the map and see it's already loaded.
	TTextureMap::const_iterator iter = m_Textures.find(strTextName);
	if (iter != m_Textures.end())
	{
		return iter->second;
	}

	// If it was not found, try to load it from the file specified, if it failed
	// delete the texture and throw an exception
	Texture* pTex = NULL;
	try
	{
		pTex = new Texture(strTextName);
	}
	catch (CException* e)
	{
		delete pTex;
		throw e;
	}

	// Store the texture and return it
	m_Textures[strTextName] = pTex;
	return pTex;
}

bool TextureManager::ReleaseTexture(const string& strTextName)
{
	// Retrieve the texture from the map
	bool found = false;
	TTextureMap::iterator iter = m_Textures.find(strTextName);
	if (iter != m_Textures.end())
	{
		// If it was found, delete it and remove the pointer from the map.
		found = true;
		if (iter->second)
			delete iter->second;
		m_Textures.erase(iter);
	}

	return found;
}