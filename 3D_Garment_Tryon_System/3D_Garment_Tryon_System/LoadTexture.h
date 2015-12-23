#pragma once
class LoadTexture
{
public:
	LoadTexture(void);
	~LoadTexture(void);

public:
	bool LoadTGA(const char *file);          //����TGA�ļ�
    void FreeImage();                        // �ͷ��ڴ� 
	
public:
    unsigned int ID;                        // ���������ID�� 
    int imageWidth;                         // ͼ����
    int imageHeight;                        // ͼ��߶�
    unsigned char *image;                   // ָ��ͼ�����ݵ�ָ�� 
    unsigned int type;                      // ͼ������GL_RGB ��GL_RGBA 
};

