/***************************
	����	Garment
	����	����ǿ
	����	������
	����	10.06.2012
*****************************/



#pragma once

////////////////////////////////////////
//		ע����Ҫ�����
//#include "Seam.h"
#include "Cloth.h"

#include "NetGrid.h"


class Garment
{
public:
	/**���캯��*/
	Garment(void);
	/**��������*/
	~Garment(void);
	/**�������ƴ���*/
	void numIteration(int number,NetGrid * netGrid);
	void CollisonIteration(NetGrid * netGrid);
		/**������Ƭ*/
	vector<Cloth> allCloth;
	/**��ȡ����  д�����еĶ�ȡ���� һ�ε���*/
	bool garmentRead();
	private:
	/**Ϊ���е��ʵ���ӵ���*/
	void setSpringAll();
	/**����Ƿ����*/
	bool isOverSeam();
	/**�����ײ*/
	bool collision(NetGrid * netGrid);
	/**��������*/
	bool Iteration(NetGrid * netGrid);
	/**�����*/
	bool readSeam(char * loc);
	/**��ȡ��Ƭ  Ŀǰ��ֱ��д��*/
	bool readCloth(char * loc);
};