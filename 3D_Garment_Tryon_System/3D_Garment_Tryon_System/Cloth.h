/***************************
	����	cloth
	����	����ǿ
	����	��Ƭ����
	����	10.04.2012
*****************************/



#pragma once


//////////////////////////////////////////
//		ע��	��Ҫ������
#include "Mass.h" 
//#include "BoxCloth.h"

//#include <vector>
//using namespace std;


class Cloth
{
public:
	/**���캯��*/
	Cloth(void);
//	/**������Ƭ���� ��ȡ��Ƭ*/
//	Cloth(int _clothflag);
	/**��������*/
	~Cloth(void);
	/**��ȡ��Ƭ*/
	bool readClothFile(int loc);
	/**��ȡ�·����ʵ㼯��*/
	vector<Mass*> * getVectorMass();
	/**��ϵ�*/
	vector<Mass*> massSeam;
	/**��ϵ�*/
	vector<Mass*> massSeam1;
	/**��Ƭ��ŵ��ʵ㼯��*/
	vector<Mass*> massCloth;
private:
	//��־λ
	int clothflag;
};

