//
//  TexManager.h
//  OpenGLT1
//
//  Created by Peter Lockett on 08/07/2013.
//  Copyright (c) 2013 Peter Lockett. All rights reserved.
//
//Todo thread safety
#ifndef OpenGLT1_TexManager_h
#define OpenGLT1_TexManager_h

#include <map>
#include <glfw3.h>

class TexManager
{
public:
    static TexManager* GetInstance();
    void foo(){printf("bar\n");}
    
private:
    TexManager(){printf("Texute manager instance created\n");}
    GLuint GetTexure(char *tName);
    
    std::map<char*, GLuint> m_TextureMap;
    std::map<char*, GLuint>::iterator m_TexIter;
    
    
public:
    GLuint LoadTexture(char* tName);
    void ReleaseTexture(char *tName);
};

#endif
