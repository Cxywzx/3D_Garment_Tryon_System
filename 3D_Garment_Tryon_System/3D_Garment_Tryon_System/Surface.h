#pragma once
#include "Dot.h"

class Surface
{
public:
	Surface(void);
	~Surface(void);
	Surface(Dot tmpp1,Dot tmpp2,Dot tmpp3);

public:
	Dot p1;	//һ�����������������
	Dot p2;
	Dot p3;
	Dot nv;	//������
};

