//
//  TexManager.cpp
//  OpenGLT1
//
//  Created by Peter Lockett on 08/07/2013.
//  Copyright (c) 2013 Peter Lockett. All rights reserved.
//
#include "TexManager.h"

static TexManager* m_Instance;

TexManager* TexManager::GetInstance() // Compiler (GCC atleast) would not be aware of the static m_Instance symbol if not added to to the compilation unit.
{
    if (m_Instance == NULL) // If the object is not yet initialised
        m_Instance = new TexManager(); // Initialize it
        
        return m_Instance;
}

GLuint TexManager::GetTexure(char* tName)
{
    //auto it = m_TextureMap.begin();

	return NULL;
}

GLuint TexManager::LoadTexture(char *tName){
	return NULL;
}
