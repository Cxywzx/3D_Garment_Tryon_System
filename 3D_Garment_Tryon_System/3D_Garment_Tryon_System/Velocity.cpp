/***************************
	����	Velocity
	����	����ǿ
	����	�ٶȵ���
	����	10.04.2012
*****************************/

#include "StdAfx.h"
#include "Velocity.h"
#include <math.h>

/***���캯��*/
Velocity::Velocity(void)
{
	x=0;
	y=0;
	z=0;
	speed = 0;
}
/**���ع��캯��	�������ķ��� �Զ������С*/
Velocity::Velocity(float _x,float _y,float _z){
	x=_x;
	y=_y;
	z=_z;
	speed = sqrt(x*x + y*y + z*z);
}
/**��������*/
Velocity::~Velocity(void)
{
}
/**��ȡx����ֵ*/
float Velocity::getX(){
	return x;
}
/**��ȡy����ֵ*/
float Velocity::getY(){
	return y; 
}
/**��ȡz����ֵ*/
float Velocity::getZ(){
	return z;
}
/**��ȡ���Ĵ�С*/
float Velocity::getSpeed(){
return speed;
}
/**����x����ֵ*/
void Velocity::setX(float _x){
	x = _x;
}
/**����y����ֵ*/
void Velocity::setY(float _y){
	y = _y;
}
/**����z����ֵ*/
void Velocity::setZ(float _z){
	z = _z;
}
/**����speed��ֵ�ı��ٶ��������ֵ ��ʱ���򲻱�*/
void Velocity::setSpeed(float _speed){
	float tmpSwap = _speed/speed;
	x=x * tmpSwap;
	y=y * tmpSwap;
	z=z * tmpSwap;
}
 /**���ؼӷ�*/
Velocity Velocity::operator+(Velocity vel){
	Velocity tmpforce = Velocity(x+vel.x,y+vel.y,z+vel.z);
	return tmpforce; 
}
/**������֮�����*/
Velocity Velocity::operator-(Velocity vel){
	Velocity tmpforce = Velocity(x-vel.x,y-vel.y,z-vel.z);
	return tmpforce; 
}


