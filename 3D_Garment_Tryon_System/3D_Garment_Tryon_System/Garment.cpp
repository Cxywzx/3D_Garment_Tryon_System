/***************************
	����	Garment
	����	����ǿ
	����	������
	����	10.06.2012
*****************************/

#include "StdAfx.h"
#include "Garment.h"
#include "math.h"
//�������С									//debug
#define SEAMFORCE 1000.0f   //mass.cpp
//������С									//debug
#define zhongli 1000.0f 
//���ڵ���������������������ײ					//debug
#define numdiedadi 50
//���ڵ��ɵ���ϵ��		���Բ���					//debug
#define tanhuang 10.0f


extern vector<vector<Mass*>> showMass_larm;
extern vector<vector<Mass*>> showMass_rarm;
extern vector<vector<Mass*>*> showMass_body_down;

extern vector<vector<Mass*>> showMass_body_centerf;
extern vector<vector<Mass*>> showMass_body_centerb;

extern vector<vector<Mass*>> showMass_body_ling1;
extern vector<vector<Mass*>> showMass_body_ling2;
extern vector<vector<Mass*>> showMass_body_ling3;





extern int isIn[180][80][180];

/**���캯��*/
Garment::Garment(void){
	allCloth = vector<Cloth>();
}
/**��������*/
Garment::~Garment(void){

}

/**��ȡ����  д�����еĶ�ȡ���� һ�ε���*/
bool Garment::garmentRead(){
	if(!readCloth("ff")){
		perror("Garment readCloth() ����\n");
		return false;
	}
	if(!readSeam("dd")){
		perror("Garment readSeam() ����\n");
		return false;
	}

	//��ӵ���
	setSpringAll();
	return true;
}


/**��ȡ��Ƭ  Ŀǰ��ֱ��д�� loc��ǰ�·�����*/
bool Garment::readCloth(char * loc){
	//�Լ�д��   allCloth  PXWIDTH
	
	Cloth *tmp = new Cloth();
	if(!tmp->readClothFile(1)){
		perror("Cloth readClothFile ����\n");
	}
	allCloth.push_back(*tmp);

	tmp = new Cloth();
	if(!tmp->readClothFile(2)){
		perror("Cloth readClothFile ����\n");	
	}
	allCloth.push_back(*tmp);


	tmp = new Cloth();
	if(!tmp->readClothFile(3)){
		perror("Cloth readClothFile ����\n");	
	}
	allCloth.push_back(*tmp);


	tmp = new Cloth();
	if(!tmp->readClothFile(4)){
		perror("Cloth readClothFile ����\n");	
	}
	allCloth.push_back(*tmp);
	
	tmp = new Cloth();
	if(!tmp->readClothFile(5)){
		perror("Cloth readClothFile ����\n");	
	}
	allCloth.push_back(*tmp);
	
	tmp = new Cloth();
	if(!tmp->readClothFile(6)){
		perror("Cloth readClothFile ����\n");	
	}
	allCloth.push_back(*tmp);

	return true;
}
/**�����*/
bool Garment::readSeam(char * loc){
	int sizeCloth = allCloth.size()/2;


	for(int i = 0;i < sizeCloth/2; i ++){
		for(int j = 0; j < allCloth.at(i).massCloth.size();j ++){

			allCloth.at(i*2).getVectorMass()->at(j)->seamForce = Force(0,0,-SEAMFORCE);

			allCloth.at(i*2 + 1).getVectorMass()->at(j)->seamForce = Force(0,0,SEAMFORCE);
			//
		}
	}


	for(int i = 0;i < sizeCloth; i ++){
		for(int j = 0; j < allCloth.at(2*i).massSeam.size();j ++){
			allCloth.at(2*i).massSeam.at(j)->seamMassPoint=(allCloth.at(2*i+1).massSeam.at(j));
			allCloth.at(2*i).massSeam.at(j)->seamForce = Force(0,0,-SEAMFORCE);
			allCloth.at(2*i+1).massSeam.at(j)->seamMassPoint=(allCloth.at(2*i).massSeam.at(j));
			allCloth.at(2*i+1).massSeam.at(j)->seamForce = Force(0,0,SEAMFORCE);

			Spring *tmpSring = new Spring(1,allCloth.at(2*i).massSeam.at(j));
			tmpSring->setConnectedMass(allCloth.at(2*i+1).massSeam.at(j));
			allCloth.at(2*i).massSeam.at(j)->massSpring.push_back(tmpSring);
			allCloth.at(2*i).massSeam.at(j)->massSpring.push_back(tmpSring);

			tmpSring = new Spring(1,allCloth.at(2*i+1).massSeam.at(j));
			tmpSring->setConnectedMass(allCloth.at(2*i).massSeam.at(j));
			allCloth.at(2*i+1).massSeam.at(j)->massSpring.push_back(tmpSring);
			allCloth.at(2*i+1).massSeam.at(j)->massSpring.push_back(tmpSring);
			//
		}
	}
	

	//for(int i = 0;i < sizeCloth; i ++){
	//	for(int j = 0; j < allCloth.at(2*i).massSeam1.size();j ++){
	//		allCloth.at(2*i).massSeam1.at(j)->setSeamPoint(allCloth.at(2*i+1).massSeam1.at(j));
	//		allCloth.at(2*i+1).massSeam1.at(j)->setSeamPoint(allCloth.at(2*i).massSeam1.at(j));
	//	}
	//}

	int sizearmwidth = allCloth.at(2).massSeam1.size();
	
	int bodysize =allCloth.at(0).massSeam1.size()/2;

	for(int i = 0;i < sizearmwidth; i ++){
		/*allCloth.at(0).massSeam1.at(i)->setSeamPoint(allCloth.at(2).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(4).massSeam1.at(i));*/


		Spring *tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(2).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(4).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		/*allCloth.at(2).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i));
		allCloth.at(4).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i+bodysize));*/


		tmpSring = new Spring(1,allCloth.at(2).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i));
		allCloth.at(2).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(2).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(4).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(4).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(4).massSeam1.at(i)->massSpring.push_back(tmpSring);

		/*allCloth.at(1).massSeam1.at(i)->setSeamPoint(allCloth.at(3).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(5).massSeam1.at(i));*/

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(3).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(5).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		/*allCloth.at(3).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i));
		allCloth.at(5).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i+bodysize));*/

		tmpSring = new Spring(1,allCloth.at(3).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i));
		allCloth.at(3).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(3).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(5).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(5).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(5).massSeam1.at(i)->massSpring.push_back(tmpSring);
	}

	//sizearmwidth = bodysize -sizearmwidth;

	for(int i = sizearmwidth;i < bodysize; i ++){
		allCloth.at(0).massSeam1.at(i)->setSeamPoint(allCloth.at(1).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(0).massSeam1.at(i)->seamForce = Force(0,0,-SEAMFORCE);
		allCloth.at(0).massSeam1.at(i+bodysize)->seamForce = Force(0,0,-SEAMFORCE);

		allCloth.at(1).massSeam1.at(i)->setSeamPoint(allCloth.at(0).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i+bodysize)->setSeamPoint(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(1).massSeam1.at(i)->seamForce = Force(0,0,SEAMFORCE);
		allCloth.at(1).massSeam1.at(i+bodysize)->seamForce = Force(0,0,SEAMFORCE);

		Spring *tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i));
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(0).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(1).massSeam1.at(i+bodysize));
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(0).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i));
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i)->massSpring.push_back(tmpSring);

		tmpSring = new Spring(1,allCloth.at(1).massSeam1.at(i+bodysize));
		tmpSring->setConnectedMass(allCloth.at(0).massSeam1.at(i+bodysize));
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
		allCloth.at(1).massSeam1.at(i+bodysize)->massSpring.push_back(tmpSring);
	}

	return true;
}

/**Ϊ���е��ʵ���ӵ���*///����㵽���ʵ����  �����ȥ
void Garment::setSpringAll(){
	int allClothLength = allCloth.size();
	int clothLength =0;
	float tmpx;
	float tmpy;
	float tmpz;

	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			for(int k = 0;k < clothLength;k ++){

				if(j == k){
					continue;
				}

				tmpx = allCloth.at(i).getVectorMass()->at(j)->x  -  allCloth.at(i).getVectorMass()->at(k)->x;
				if(tmpx > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}
				tmpy = allCloth.at(i).getVectorMass()->at(j)->y  -  allCloth.at(i).getVectorMass()->at(k)->y;
				if(tmpy > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}
				tmpz = allCloth.at(i).getVectorMass()->at(j)->z  -  allCloth.at(i).getVectorMass()->at(k)->z;
				if(tmpz > STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					continue;
				}

				float tmplength = sqrt(
									tmpx * tmpx + tmpy * tmpy + tmpz * tmpz
								);

				if(tmplength < STRUCTLENGTH  + STRUCTLENGTH / 10.0f){
					Spring *tmpSring = new Spring(1,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}else if(tmplength < STRUCTLENGTH * 1.4142135623f  + STRUCTLENGTH * 1.4142135623f / 10.0f){
					Spring *tmpSring = new Spring(2,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}else if(tmplength < STRUCTLENGTH * 2.0f  + STRUCTLENGTH * 2.0f / 10.0f){
					Spring *tmpSring = new Spring(3,allCloth.at(i).getVectorMass()->at(j));

					tmpSring->setConnectedMass(allCloth.at(i).getVectorMass()->at(k));

					allCloth.at(i).getVectorMass()->at(j)->massSpring.push_back(tmpSring);

				}
				
			}

		}
	}
}

/**�������ƴ���*/
void Garment::numIteration(int number,NetGrid * netGrid){
	//int num = 0;
	while(!Iteration(netGrid)){
		//num++;
	}
	//num++;

	int i = numdiedadi;
	while(i--){
		CollisonIteration(netGrid);
	}


	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										���·����°벿��

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile1d;				//������ļ�showMass_body_down
	//dataFile1d = fopen("bodydown_out.txt", "w");
	//
	//fprintf(dataFile1d,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1d,"#  Num verts:  %d\n",showMass_body_down.size()*showMass_body_down.at(0)->size()+showMass_body_down.size());
	//fprintf(dataFile1d,"#  Num rc: %d %d\n",showMass_body_down.size(),showMass_body_down.at(0)->size()+1);
	//fprintf(dataFile1d,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_down.size(); i++)			//��
	//{
	//	for(int j = 0; j < showMass_body_down.at(i)->size(); j++)		//��
	//	{
	//		fprintf(dataFile1d,"v %f %f %f\n",showMass_body_down.at(i)->at(j)->x,showMass_body_down.at(i)->at(j)->y,showMass_body_down.at(i)->at(j)->z);
	//	}
	//	fprintf(dataFile1d,"v %f %f %f\n",showMass_body_down.at(i)->at(0)->x,showMass_body_down.at(i)->at(0)->y,showMass_body_down.at(i)->at(0)->z);
	//}


	//fclose(dataFile1d);


	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										���·����м�ǰ�벿��

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	
	//FILE *dataFile1centerf;				//������ļ�showMass_body_centerf
	//dataFile1centerf = fopen("bodycenterf_out.txt", "w");
	//
	//fprintf(dataFile1centerf,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1centerf,"#  Num verts:  %d\n",showMass_body_centerf.size()*showMass_body_centerf.at(0).size());
	//fprintf(dataFile1centerf,"#  Num rc: %d %d\n",showMass_body_centerf.size(),showMass_body_centerf.at(0).size());
	//fprintf(dataFile1centerf,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_centerf.size(); i++)			//��
	//{
	//	for(int j = 0; j < showMass_body_centerf.at(i).size(); j++)		//��
	//	{
	//		fprintf(dataFile1centerf,"v %f %f %f\n",showMass_body_centerf.at(i).at(j)->x,showMass_body_centerf.at(i).at(j)->y,showMass_body_centerf.at(i).at(j)->z);
	//	}
	//}


	//fclose(dataFile1centerf);

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										���·����м�ǰ�벿��

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile1centerb;				//������ļ�showMass_body_centerf
	//dataFile1centerb = fopen("bodycenterb_out.txt", "w");
	//
	//fprintf(dataFile1centerb,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile1centerb,"#  Num verts:  %d\n",showMass_body_centerb.size()*showMass_body_centerb.at(0).size());
	//fprintf(dataFile1centerb,"#  Num rc: %d %d\n",showMass_body_centerb.size(),showMass_body_centerb.at(0).size());
	//fprintf(dataFile1centerb,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_body_centerb.size(); i++)			//��
	//{
	//	for(int j = 0; j < showMass_body_centerb.at(i).size(); j++)		//��
	//	{
	//		fprintf(dataFile1centerb,"v %f %f %f\n",showMass_body_centerb.at(i).at(j)->x,showMass_body_centerb.at(i).at(j)->y,showMass_body_centerb.at(i).at(j)->z);
	//	}
	//}


	//fclose(dataFile1centerb);


	

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										�����ֱ�

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile2;				//������ļ�
	//dataFile2 = fopen("arml_out.txt", "w");
	//
	//fprintf(dataFile2,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile2,"#  Num verts:  %d\n",showMass_larm.size()*showMass_larm.at(0).size()+showMass_rarm.size());
	//fprintf(dataFile2,"#  Num rc: %d %d\n",showMass_larm.size(),showMass_larm.at(0).size()+1);
	//fprintf(dataFile2,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_larm.size(); i++)			//��
	//{
	//	for(int j = 0; j < showMass_larm.at(i).size(); j++)		//��
	//	{
	//		fprintf(dataFile2,"v %f %f %f\n",showMass_larm.at(i).at(j)->x,showMass_larm.at(i).at(j)->y,showMass_larm.at(i).at(j)->z);
	//	}
	//	fprintf(dataFile2,"v %f %f %f\n",showMass_larm.at(i).at(0)->x,showMass_larm.at(i).at(0)->y,showMass_larm.at(i).at(0)->z);
	//}


	//fclose(dataFile2);



	/*//////////////////////////////////////////////////////////////////////////////////////////////////////

										�����ֱ�

	///////////////////////////////////////////////////////////////////////////////////////////////////////*/
	
	//FILE *dataFile3;				//������ļ�
	//dataFile3 = fopen("armr_out.txt", "w");
	//
	//fprintf(dataFile3,"#  ----------------------------------------------------------\n");

	//fprintf(dataFile3,"#  Num verts:  %d\n",showMass_rarm.size()*showMass_rarm.at(0).size()+showMass_rarm.size());
	//fprintf(dataFile3,"#  Num rc: %d %d\n",showMass_rarm.size(),showMass_rarm.at(0).size()+1);
	//fprintf(dataFile3,"#  Num tElems: 8\n");

	//for(int i = 0; i < showMass_rarm.size(); i++)			//��
	//{
	//	for(int j = 0; j < showMass_rarm.at(i).size(); j++)		//��
	//	{
	//		fprintf(dataFile3,"v %f %f %f\n",showMass_rarm.at(i).at(j)->x,showMass_rarm.at(i).at(j)->y,showMass_rarm.at(i).at(j)->z);
	//	}
	//	fprintf(dataFile3,"v %f %f %f\n",showMass_rarm.at(i).at(0)->x,showMass_rarm.at(i).at(0)->y,showMass_rarm.at(i).at(0)->z);
	//}


	//fclose(dataFile3);

}

/**��������*/
bool Garment::Iteration(NetGrid * netGrid){
	
	//�ı�

	int allClothLength = allCloth.size();
	int clothLength =0;
	//�ı��ʵ�����
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeAll();
		}
	}


	/**�����ײ*/
	/*if(isCollision(netGrid)){
		return false;
	}*/
	collision(netGrid);
	//������ײ��
	//��ײ�ĵ�  ���˶�
	


	/**�������Ƿ��Ͻ���  �ı���ʵ�����*/
	//�ж�
	if(isOverSeam()){
		for(int i = 0;i < allClothLength; i ++){
			clothLength = allCloth.at(i).getVectorMass()->size();
			for(int j = 0;j < clothLength;j ++){
				allCloth.at(i).getVectorMass()->at(j)->seamMassPoint = NULL;
				allCloth.at(i).getVectorMass()->at(j)->seamForce = Force();
				//allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
				allCloth.at(i).getVectorMass()->at(j)->galavity = Force(0,zhongli,0);
				for(int k = 0;k < allCloth.at(i).getVectorMass()->at(j)->massSpring.size();k ++ ){
					allCloth.at(i).getVectorMass()->at(j)->massSpring.at(k)->kFactor = tanhuang;
				}
			}
		}
		return true;
	}else{
		//�ı�վ��λ��
		for(int i = 0;i < allClothLength; i ++){
			clothLength = allCloth.at(i).getVectorMass()->size();
			for(int j = 0;j < clothLength;j ++){
				allCloth.at(i).getVectorMass()->at(j)->changeLocation();
				//allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
			}
		}
		return false;
	}
}



/**��ײ��������*/
void Garment::CollisonIteration(NetGrid * netGrid){
	
	int allClothLength = allCloth.size();
	int clothLength =0;
	//�ı��ʵ�����
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeAll();
		}
	}
	
	/**�����ײ*/
	/*if(isCollision(netGrid)){
		return;
	}*/
	collision(netGrid);
	//������ײ��
	//��ײ�ĵ�  ���˶��ٶȷ���
	

	//�ı�վ��λ��
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			allCloth.at(i).getVectorMass()->at(j)->changeLocation();
			allCloth.at(i).getVectorMass()->at(j)->resetVelocity();
		}
	}
	
}



/**����Ƿ����*/
bool Garment::isOverSeam(){
	int allClothLength = allCloth.size();
	int clothLength =0;
	Mass * tmpMass;
	bool isover = true;
	int tmpum=0;
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			tmpMass = allCloth.at(i).getVectorMass()->at(j);
			if(tmpMass->seamMassPoint){
				float tmpX = tmpMass->x - tmpMass->seamMassPoint->x;
				float tmpY = tmpMass->y - tmpMass->seamMassPoint->y;
				float tmpZ = tmpMass->z - tmpMass->seamMassPoint->z;

				if(sqrt(tmpX*tmpX + tmpY*tmpY + tmpZ * tmpZ) < 3.0)
				{
					tmpum ++;
					//isover = false;
				}
			}
		}
	}

	if(tmpum < 5){
		isover = false;
	}
	return isover;
}



/**�����ײ*/
bool Garment::collision(NetGrid * netGrid){
	float gap = netGrid->gap;
	float tmplength = netGrid->length;
	float tmpwidth = netGrid->width;
	float tmpheight = netGrid->height;
	//�������ǰ����netgrid�е�λ��  ���жϸ�λ���Ƿ�Ϊ1
	int allClothLength = allCloth.size();
	int clothLength =0;
	//�ж��Ƿ���ײ   ���������ٶ�  
	Mass * tmpMass;


	//FILE *dataFile2;				//������ļ�
	//dataFile2 = fopen("gai_out.txt", "w");
	for(int i = 0;i < allClothLength; i ++){
		clothLength = allCloth.at(i).getVectorMass()->size();
		for(int j = 0;j < clothLength;j ++){
			tmpMass = allCloth.at(i).getVectorMass()->at(j);

			float x =allCloth.at(i).getVectorMass()->at(j)->x + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getX() * 0.005f;
			float y =allCloth.at(i).getVectorMass()->at(j)->y + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getY() * 0.005f;
			float z =allCloth.at(i).getVectorMass()->at(j)->z + allCloth.at(i).getVectorMass()->at(j)->massSpeed.getZ() * 0.005f;

			int tmpx = (x + tmplength/2 )/gap;
			int tmpy = (156- y)/gap;
			int tmpz = (tmpwidth/2 - z)/gap;
			if(isIn[tmpx][tmpz][tmpy]){
				//�����ٶ�
				tmpMass->resetVelocity();
				
			}
		}
	}
	/*fprintf(dataFile2,"\n\n\n");
	fclose(dataFile2);*/
	return false;
}