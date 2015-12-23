/***************************
	����	Mass
	����	����ǿ
	����	������
	����	10.05.2012
	ע��	ʹ��ʱ�����÷����
			Ȼ����changeAll������ɸı�
*****************************/

#pragma once

////////////////////////////////////////
//		ע����Ҫ�����

//#include "Force.h"
#include "Velocity.h"

#include <vector>
using namespace std;

#include "Spring.h"
class Spring;


class Mass
{
public:
	/**���캯�� Ĭ������Ϊ0��0��0 �������setSeamGorce()���÷����*/
	Mass(void);
	/**���캯�� ���������������setSeamGorce()���÷����*/
	Mass(float _x,float _y,float _z);
	/**������иı�*/
	void changeAll();
	/**�ı�λ��*/
	void changeLocation();
	/**��������*/
	~Mass(void);
	//ָ������x
	float x;
	//ָ������y
	float y;
	//ָ������z
	float z;
	/**���÷�ϵ�*/
	void setSeamPoint(Mass * _seamMassPoint);
	/**��ϵ�*/
	Mass * seamMassPoint;
	/**���ɼ���*/
	vector<Spring*> massSpring;
	/**�����*/
	Force seamForce;
	void resetVelocity();
//private:
	/**���õ������*/
	void computeSeamForce();
	/**�������*/
	void computeAllForce();
	/**���㵯�ɺ���*/
	void computeSpringForce();
	/**�����ٶ�*/
	void changeVelocity();


	/**����*/
	Force galavity;
	/**���ɺ���*/
	Force springForce;
	/**����*/
	Force allForce;
	/**�ٶȼ���*/
	Velocity massSpeed;
};