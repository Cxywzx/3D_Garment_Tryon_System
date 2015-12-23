#include "StdAfx.h"
#include "TextureMap.h"
#include<stdio.h>
#include<GL/glut.h>
#include<GL/glu.h>	
#include<GL/glaux.h>
#pragma comment(lib, "glaux.lib")

TextureMap::TextureMap(void)
{
	loadTexture = new LoadTexture();
}


TextureMap::~TextureMap(void)
{
	if(loadTexture)
		delete loadTexture;
	loadTexture = NULL;
}

/** ����TGA�ļ����������� */
bool TextureMap::LoadTextureTGA(const char* fileName)
{
	if(!loadTexture->LoadTGA(fileName))
	{
		exit(0);
	}
	
   return true;
}

void TextureMap::SetTexturePara(LoadTexture *texture)
{
	/** ��������������� */
	glGenTextures(1, &texture->ID);
   
    /** ����������� */
    glBindTexture(GL_TEXTURE_2D, texture->ID);
	
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   
	/** �������� */
   	gluBuild2DMipmaps(GL_TEXTURE_2D, texture->type, texture->imageWidth,
	                  texture->imageHeight, texture->type, GL_UNSIGNED_BYTE,
	                  texture->image);

      /* glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	   glGenTextures(1,texName);

	   glBindTexture(GL_TEXTURE_2D , *texName);

	   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImg.imgWidth,textureImg.imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImg.data);   */
}
