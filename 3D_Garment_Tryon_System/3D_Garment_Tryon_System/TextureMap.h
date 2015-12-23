#pragma once
#include "LoadTexture.h"



class TextureMap
{
public:
	TextureMap(void);
	~TextureMap(void);

public:
	bool LoadTextureTGA(const char* fileName);		 // ����TGA�ļ�Ϊ���� 
	void SetTexturePara(LoadTexture *texture);

	LoadTexture *loadTexture;
	
};

