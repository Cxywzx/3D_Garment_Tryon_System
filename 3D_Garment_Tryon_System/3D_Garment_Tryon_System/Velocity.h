/***************************
	����	Velocity
	����	����ǿ
	����	�ٶȵ���
	����	10.04.2012
*****************************/

#pragma once
class Velocity
{
public:
	/**���캯��*/
	Velocity(void);
	/**���ع��캯��	�������ķ��� �Զ������С*/
	Velocity(float _x,float _y,float _z);
	/**������֮��ӷ�*/
	Velocity operator+(Velocity vel);
	/**������֮�����*/
	Velocity operator-(Velocity vel);
	/**��ȡx����ֵ*/
	float getX();
	/**��ȡy����ֵ*/
	float getY();
	/**��ȡz����ֵ*/
	float getZ();
	/**��ȡ���Ĵ�С*/
	float getSpeed();
	/**����x����ֵ*/
	void setX(float _x);
	/**����y����ֵ*/
	void setY(float _y);
	/**����z����ֵ*/
	void setZ(float _z);
	/**����strength��ֵ�ı�strength�������ֵ*/
	void setSpeed(float _speed);
	/**��������*/
	~Velocity(void);
	//�ٶ�ֵ
	float speed;
	//����
	float x;
	float y;
	float z;
};

