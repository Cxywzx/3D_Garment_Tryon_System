/***************************
	����	Spring
	����	����ǿ
	����	������
	����	10.05.2012
*****************************/

#pragma once


////////////////////////////////////////
//		ע����Ҫ�����
#include "Force.h"

#include "Mass.h"

//����ṹ����ԭ��
#define STRUCTLENGTH 1.8f       //Ҫ��cloth �������С

class Mass;



class Spring
{
public:
	/**���캯��*/
	Spring(Mass * _current);
	/**���ع��캯��	���赯������ 1 2 3*/
	Spring(int _kind,Mass * _current);
	/**���õ��������ĵ�*/
	void setConnectedMass(Mass * _ConnectedMass);
	/**��������ĵ�ָ��*/
	Mass * getConnectedMass();
	/**��ȡ����ϵ��*/
	float getFactor();
	/**��ȡ��ǰ������*/
	Force getForce();
	/**��������*/
	~Spring(void);
	int getkind();
	/**����ϵ��*/
	float kFactor;
	/**��ȡ���ɳ���*/
	float getLength();
private:
	//void init();
	/**���㵯�ɵ�ǰ�ĵ���ϵ��   ��Ҫ����д*/
	float computeFactor();
	/**�������� 	1�������� 2 ���е��� 3 ��������*/
	int kind;
	/**�������ڳ���	*/
	float length;
	/**�������ڳ���	*/
	float nowlength;
	
	/**��ǰ��ĵ�ַ*/
	Mass * currentMass;
	/**������ĵ�ַ*/
	Mass * connectedMass;
};
