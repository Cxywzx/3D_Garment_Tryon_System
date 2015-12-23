/***************************
	����	Force
	����	����ǿ
	����	������
	����	10.04.2012
*****************************/


#include "StdAfx.h"
#include "Force.h"
#include <math.h>


/***���캯��*/
Force::Force(void)
{
	x=0;
	y=0;
	z=0;
	strength = 0;
}
/**���ع��캯��	�������ķ��� �Զ������С*/
Force::Force(float _x,float _y,float _z){
	x=_x;
	y=_y;
	z=_z;
	strength = sqrt(x*x + y*y + z*z);
}
/**��������*/
Force::~Force(void)
{
}
/**��ȡx����ֵ*/
float Force::getX(){
	return x;
}
/**��ȡy����ֵ*/
float Force::getY(){
	return y; 
}
/**��ȡz����ֵ*/
float Force::getZ(){
	return z;
}
/**��ȡ���Ĵ�С*/
float Force::getStrength(){
return strength;
}
/**��������ֵ*/
void Force::updateStrength(){
	strength = sqrt(x*x + y*y + z*z);
}
/**����x����ֵ*/
void Force::setX(float _x){
	x = _x;
}
/**����y����ֵ*/
void Force::setY(float _y){
	y = _y;
}
/**����z����ֵ*/
void Force::setZ(float _z){
	z = _z;
}
/**����strength��ֵ�ı�strength�������ֵ ��ʱ���򲻱�*/
void Force::setStrength(float _strength){
	float tmpSwap = _strength/strength;
	x=x * tmpSwap;
	y=y * tmpSwap;
	z=z * tmpSwap;
}
 /**���ؼӷ�*/
Force Force::operator+(Force force){
	Force tmpforce = Force(x+force.x,y+force.y,z+force.z);
	return tmpforce; 
}
/**������֮�����*/
Force Force::operator-(Force force){
	Force tmpforce = Force(x-force.x,y-force.y,z-force.z);
	return tmpforce; 
}
