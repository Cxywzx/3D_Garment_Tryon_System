
/***************************
	����	Force
	����	����ǿ
	����	������
	����	10.04.2012
*****************************/

#pragma once



class Force
{
public:
	/**���캯��*/
	Force(void);
	/**���ع��캯��	�������ķ��� �Զ������С*/
	Force(float _x,float _y,float _z);
	/**������֮��ӷ�*/
	Force operator+(Force strg);
	/**������֮�����*/
	Force operator-(Force strg);
	/**��ȡx����ֵ*/
	float getX();
	/**��ȡy����ֵ*/
	float getY();
	/**��ȡz����ֵ*/
	float getZ();
	/**��ȡ���Ĵ�С*/
	float getStrength();
	/**����x����ֵ*/
	void setX(float _x);
	/**����y����ֵ*/
	void setY(float _y);
	/**����z����ֵ*/
	void setZ(float _z);
	/**����strength��ֵ�ı�strength�������ֵ*/
	void setStrength(float _strength);
	/**��������ֵ*/
	void updateStrength();
	/**��������*/
	~Force(void);
	//����ֵ
	float strength;
	//����
	float x;
	float y;
	float z;
};

