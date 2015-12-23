#pragma once
#include "Surface.h"

class BodyPart
{
public:
	vector<Dot> dotCollection;		//���ÿ�������ĵ�ļ���
	vector<Surface> surfaceCollection;		//���ÿ����������ļ���
	vector<vector<Dot>> circleCollection;	//��һ��Ȧ��������ʷֺ��һ��Ȧ�ĵ㣬���Ȧ��vector<Dot>���͵�
											//һ��circleCollection������Ȧ�ļ���

public:
	BodyPart(void);
	~BodyPart(void);
};

