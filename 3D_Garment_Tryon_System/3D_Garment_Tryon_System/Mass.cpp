/***************************
	����	Mass
	����	����ǿ
	����	������
	����	10.05.2012
*****************************/

#include "StdAfx.h"
#include "Mass.h"
//������С									//debug
#define GALAVITY 10.0f
//�������ٶ�   ����Ϊ 0 .��������������
#define GRAVITYACCEL 10.0F
//����ʱ��									//debug
#define TIME 0.005f
//�������С										//debug
#define SEAMFORCE 1000.0f  //garment.cpp



/**���캯��*/
Mass::Mass(void){
	/**����*/
	galavity = Force();
	/**���ɺ���*/
	 springForce = Force();
	/**�����*/
	 seamForce = Force();
	/**����*/
	 allForce = Force();
	/**���ɼ���*/
	massSpring = vector<Spring*>();
	/**�ٶȼ���*/
	massSpeed = Velocity();
	//ָ������x
	 x = 0.0f;
	//ָ������y
	 y = 0.0f;
	//ָ������z
	 z = 0.0f;
	 seamMassPoint=NULL;

}

/**���캯�� ��������  */
Mass::Mass(float _x,float _y,float _z){
	/**����*/
	galavity = Force();
	/**���ɺ���*/
	 springForce = Force();
	/**�����*/
	 seamForce = Force();
	/**����*/
	 allForce = Force();
	/**���ɼ���*/
	massSpring = vector<Spring*>();
	/**�ٶȼ���*/
	massSpeed = Velocity();
	//ָ������x
	 x = _x;
	//ָ������y
	 y = _y;
	//ָ������z
	 z = _z;
	 seamMassPoint=NULL;
}

/**���㵯�ɺ���*/
void Mass::computeSpringForce(){
	int iTmpSize = massSpring.size();

	if(!seamMassPoint && iTmpSize){
		for(int i = 0;i < iTmpSize;i ++){
			springForce = springForce + massSpring.at(i)->getForce();
		}
	}else{
		springForce = Force();
	}
}

/**�����ٶ�*/
void Mass::changeVelocity(){
	//��������		����y�� ����
	float quality = GALAVITY/GRAVITYACCEL;
	//���ٶ�
	float ax = allForce.getX()/quality;
	float ay = allForce.getY()/quality;
	float az = allForce.getZ()/quality;
	//����ʱ�������ӵ��ٶ�
	Velocity tmpVol = Velocity(ax*TIME,ay*TIME,az*TIME);
	massSpeed = massSpeed+  tmpVol;
}


void Mass::resetVelocity(){
	massSpeed = Velocity();
}


/**�ı�λ��*/
void Mass::changeLocation(){
	x += massSpeed.getX() * TIME;
	y += massSpeed.getY() * TIME;
	z += massSpeed.getZ() * TIME;
}

/**���÷�ϵ�*/
void Mass::setSeamPoint(Mass * _seamMassPoint){
	seamMassPoint =_seamMassPoint;
}

/**���õ������*/
void Mass::computeSeamForce(){
	//��ʱΪ�㶨ֵ
	//if(seamMassPoint){
	//	 
	//}
}
/**�������*/
 void Mass::computeAllForce(){
	allForce = springForce  + galavity + seamForce;
	//if(allForce.getStrength() > 100.0){
	//	perror("fuck");
	//}
}

/**������иı�*/
void Mass::changeAll(){
	//���㵯�ɺ���
	computeSpringForce();
	//���㵯�����

	//computeSeamForce();
	//�������
	computeAllForce();
	//�ı��ٶ�
	changeVelocity();
	//�ı�λ��
	//changeLocation();
}

/**��������*/
Mass::~Mass(void){
	massSpring.clear();
	delete seamMassPoint;
}