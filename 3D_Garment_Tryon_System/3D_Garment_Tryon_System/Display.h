
#pragma once

#include "Body.h"
#include "NetGrid.h"
#include "TextureMap.h"


#include "Garment.h"   


#define TEXTURE_COUNT	4

class Display
{
public:
	Display(CWnd *w);
	~Display(void);

	bool Init();
	bool GetDrawPen();
	void Render();
	void DrawTriangle(float x1,float y1, float z1, 
						float x2, float y2, float z2,
						float x3, float y3, float z3, int backGround);
	//void LoadTexture();
	void DrawBackground(int backGround);
	//���Ƴ�ʼ����ģ��
	void DefaultBodyDisplay(vector<BodyPart *> *data,int backGround);
	//���������ʷֺ������ģ��
	void TriangulateBodyDisplay(vector<BodyPart *> *data,int backGround);


	void SurfaceBodyDisplay(vector<BodyPart *> *data,int backGround);




	//void DefaultBoxDisplay(BoxCloth *tmpBoxCloth);
	//void BoxCollideDisplay(BoxCloth *tmpBoxCloth);

	void DefaultGarmentDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol,int backGround);
	void GarmentCollideDisplay(vector<BodyPart *> *data,vector<Cloth> * clothcol,int backGround);


	
public:
	//��ͼ����Ⱦ������
	CWnd *wnd;
	HDC m_hDC;
	HGLRC m_hRC;

	// Rotation amounts
	float xRot;
	float yRot;
	float zRot;

	//����
	TextureMap texture[TEXTURE_COUNT];
	char *textureFileName[TEXTURE_COUNT];

protected:
	bool SetPixel();
};

