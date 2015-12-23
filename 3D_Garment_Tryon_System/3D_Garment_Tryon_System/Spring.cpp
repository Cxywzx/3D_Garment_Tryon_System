/***************************
	����	Spring
	����	����ǿ
	����	������
	����	10.05.2012
*****************************/

#include "StdAfx.h"
#include "Spring.h"
#include "math.h"


//���ɵ�ǰ�ĵ���ϵ��									//debug
#define FAVTOR 10.0f 


/**���캯��*/
Spring::Spring(Mass * _current){
	kind = 1;
	//length = 0.0f;
	length = STRUCTLENGTH;
	
	kFactor = FAVTOR;
	currentMass = _current;
}
/**���ع��캯��	���赯������ 1 2 3*/
Spring::Spring(int _kind,Mass * _current){
	kind = _kind;
	//length = 0.0f;
	if(kind == 1){
		length  = STRUCTLENGTH;
	}else if(kind == 2){
		length = STRUCTLENGTH * 1.4142135623f;
	}else if(kind == 3){
		length = STRUCTLENGTH * 2.0f;
	}else{
		perror("Spring�������kindֵ���ٵ���������");
	}
	kFactor = FAVTOR;
	currentMass = _current;
	//connectedMass = _ConnectedMass;
}
/**���õ��������ĵ�*/
void Spring::setConnectedMass(Mass * _ConnectedMass){
	connectedMass = _ConnectedMass;
}
/**��ȡ��ǰ������*/
Force Spring::getForce(){
	if(connectedMass == NULL){
		perror("spring ������ĵ�ַΪ�գ�");
	}
	//���㵯��ϵ��
	computeFactor();
	//������
	Force tmpForce=Force();
	//���ɳ���
	float tmpSprLength = getLength();
	//�ж������ɵĸı�����Ƿ��С  ��С�򷵻�ֵ 0
	if(tmpSprLength - length < (length/1000.0f) 
			&& tmpSprLength - length > - (length/1000.0f))
			{
		return tmpForce;
	}
	if(tmpSprLength > 5*length){
		kFactor = 10*FAVTOR;
	}else if(tmpSprLength > 3*length){
		kFactor = 5*FAVTOR;
	}else{
		kFactor = FAVTOR;
	}

	//������
	//tmpForce.setStrength(abs(kFactor * (tmpSprLength - length)));

	//��õ������ķ���
	float changeInt = kFactor* (tmpSprLength - length)/tmpSprLength ;
	tmpForce = Force(
			(connectedMass->x-currentMass->x)*changeInt
			,(connectedMass->y-currentMass->y)*changeInt 
			,(connectedMass->z-currentMass->z)*changeInt );
	return tmpForce;
}
/**��������ĵ�ָ��*/
Mass * Spring::getConnectedMass(){
	if(connectedMass == NULL){
		perror("spring ������ĵ�ַΪ�գ�");
	}
	return connectedMass;
}
int Spring::getkind(){
	return kind;
}
/**��ȡ����ϵ��*/
float Spring::getFactor(){
	//�ȼ������ڵ��ɵ�ֵ;�ڷ���
	computeFactor();
	return kFactor;
}
/**�������ڳ���*/
float Spring::getLength(){
	if(connectedMass == NULL){
		perror("spring ������ĵ�ַΪ�գ�");
	}

	nowlength = sqrt(
				(connectedMass->x-currentMass->x)*(connectedMass->x-currentMass->x)+
				(connectedMass->y-currentMass->y)*(connectedMass->y-currentMass->y)+
				(connectedMass->z-currentMass->z)*(connectedMass->z-currentMass->z)
				);
	return nowlength;
}
/**��������*/
Spring::~Spring(void){
	if(connectedMass!=NULL){
		delete connectedMass;
	}
	if(currentMass!=NULL){
		delete currentMass;
	}
}
/**���㵯�ɵ�ǰ�ĵ���ϵ��	��Ҫ����д*/
float Spring::computeFactor(){
	if(connectedMass == NULL){
		perror("spring ������ĵ�ַΪ�գ�");
	}
	return 0.0f;
}