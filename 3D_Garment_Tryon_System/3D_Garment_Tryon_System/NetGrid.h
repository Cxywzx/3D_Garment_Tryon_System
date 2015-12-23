#pragma once

#include "Dot.h"
#include "Body.h"


class NetGrid
{
public:
	float length;
	float width;
	float height;
	float gap;

	//int ***isIn;				//�����Ƿ��������ڲ� �������ڲ���Ϊ 1������Ϊ0
	//int isIn[45][20][45];
	Dot	***centerDots;			//�������ĵ�

public:
	//NetGrid(void);
	NetGrid(float l,float w,float height,float gap);
	~NetGrid(void);

	void justifyInOrOut(Body *body);

private:
	//bool isInSurface(Dot *centerDot, vector<BodyPart *> *PartCollection);
	bool isInBody(Dot *centerDot, vector<BodyPart *> *PartCollection);
	float triangleArea(Dot *dotA, Dot *dotB, Dot *dotC);

	bool isInBody2(Dot *centerDot, vector<BodyPart *> *PartCollection, int star, int end);
	bool isInTriangle(Dot *tA, Dot *tB, Dot *tC, Dot *tP);
	float distanceOfTwoDot(Dot *dot1, Dot *dot2);
};

