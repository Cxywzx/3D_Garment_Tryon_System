#include "StdAfx.h"
#include "Body.h"
#include "MyMathFormula.h"

Body::Body(void)
{
	//�������ÿһ�����ַŵ�һ������PartCollection����
	PartCollection = vector<BodyPart *>();
	PartCollectionX = vector<BodyPart *>();
	PartCollectionY = vector<BodyPart *>();
	PartCollectionZ = vector<BodyPart *>();

	//PartCollection��Ԫ��0~19
	PartCollection.push_back(&head);	//0
	PartCollection.push_back(&neck);	//1

	PartCollection.push_back(&lhand);		//2
	PartCollection.push_back(&lforearm);
	PartCollection.push_back(&lshoulder);
	PartCollection.push_back(&lcollar);		//5
	PartCollection.push_back(&rcollar);
	PartCollection.push_back(&rshoulder);
	PartCollection.push_back(&rforearm);
	PartCollection.push_back(&rhand);		//9

	PartCollection.push_back(&chest);		//10
	PartCollection.push_back(&abdomen);
	PartCollection.push_back(&hip);		//12

	PartCollection.push_back(&lthigh);	//13
	PartCollection.push_back(&rthigh);
	PartCollection.push_back(&lshin);
	PartCollection.push_back(&rshin);	//16

	PartCollection.push_back(&lfoot);	//17
	PartCollection.push_back(&rfoot);	//18
}

Body::~Body(void)
{

}

bool Body::readOBJFile()
{
	char * filename;
	if(sex==1)	filename = "./res/1.obj";
	if(sex==0)	filename = "./res/0.obj";

/*
	��ȡobj�ļ��Ķ�������		Start
*/



	FILE *dataFile;				//������ļ�
    int count;					//���������ļ�����
    char inputLine[512];	
    int ilLen;					//�ߵĳ���
    float x, y, z;			    //��������
	dataFile = fopen(filename, "r");
    if (dataFile == NULL) {
		perror(filename);
		return false;
    }

	BodyPart * tmpvect = new BodyPart();

	for(;;) {
		if (fgets(inputLine, 500, dataFile) == NULL)
			break;			//�ļ���β

		//����ߵĳ���
		ilLen = strlen(inputLine);

		while ((ilLen > 0) && ((inputLine[ilLen - 1] == ' ') || (inputLine[ilLen - 1] == '\n')))
			ilLen--;
		

		if (inputLine[0] == 'v') {
			//����һ�����㣬�����䱣�浽���������

			if (inputLine[1] == ' ') {
			//һ������
			count = sscanf(inputLine, "v %f %f %f", &x, &y, &z);
			if (count != 3)
				continue;
				
				Dot *tmp = new Dot(x,y,z);
				tmpvect->dotCollection.push_back(*tmp);

			}
		}
		else if(inputLine[0] == '#'){
			if(strstr(inputLine,"InternalName")){
				if(strstr(inputLine,"hip")){
						tmpvect = &hip;
				} else if(strstr(inputLine,"abdomen")){
						tmpvect = &abdomen;
				}else
					if(strstr(inputLine,"chest")){
										tmpvect = &chest;
				}else
					if(strstr(inputLine,"neck")){
										tmpvect = &neck;
				}else
					if(strstr(inputLine,"head")){
										tmpvect = &head;
				}else
					if(strstr(inputLine,"lCollar")){
										tmpvect = &lcollar;
				}else
					if(strstr(inputLine,"lForeArm")){
										tmpvect = &lforearm;
				}else
					if(strstr(inputLine,"lHand")){
										tmpvect = &lhand;
				}else
					if(strstr(inputLine,"rCollar")){
										tmpvect = &rcollar;
				}else
					if(strstr(inputLine,"rForeArm")){
										tmpvect = &rforearm;
				}else
					if(strstr(inputLine,"rHand")){
										tmpvect = &rhand;
				}else
					if(strstr(inputLine,"lThigh")){
										tmpvect = &lthigh;
				}else
					if(strstr(inputLine,"lShin")){
										tmpvect = &lshin;
				}else
					if(strstr(inputLine,"lFoot")){
										tmpvect = &lfoot;
				}else
					if(strstr(inputLine,"rThigh")){
										tmpvect = &rthigh;
				}else
					if(strstr(inputLine,"rShin")){
										tmpvect = &rshin;
				}else
					if(strstr(inputLine,"rFoot")){
										tmpvect = &rfoot;
				}else
					if(strstr(inputLine,"rShldr")){
										tmpvect = &rshoulder;
				}else
					if(strstr(inputLine,"lShldr")){
										tmpvect = &lshoulder;
				}else{
					exit(-1);
				}

			}
		}
	}
	fclose(dataFile);
	


/*
	��ȡobj�ļ��Ķ�������		End
*/


/*
	������߱������ŵ���Ӧ����	Start
*/

	float yMax = 0.0;
	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			if(yMax<PartCollection.at(i)->dotCollection.at(j).y)
			{
				yMax = PartCollection.at(i)->dotCollection.at(j).y;
			}
		}
	}

	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			PartCollection.at(i)->dotCollection.at(j).x = height*PartCollection.at(i)->dotCollection.at(j).x; 
			PartCollection.at(i)->dotCollection.at(j).y = height*PartCollection.at(i)->dotCollection.at(j).y;
			PartCollection.at(i)->dotCollection.at(j).z = height*PartCollection.at(i)->dotCollection.at(j).z;
		}
	}

	for(int i=0;i<PartCollection.size() ;i++)
	{
		for(int j=0;j<PartCollection.at(i)->dotCollection.size() ;j++)
		{
			PartCollection.at(i)->dotCollection.at(j).x = PartCollection.at(i)->dotCollection.at(j).x/yMax; 
			PartCollection.at(i)->dotCollection.at(j).y = PartCollection.at(i)->dotCollection.at(j).y/yMax;
			PartCollection.at(i)->dotCollection.at(j).z = PartCollection.at(i)->dotCollection.at(j).z/yMax;
		}
	}


/*
	������߱������ŵ���Ӧ����	End
*/

	return true;
}

void Body::triangulate()
{
	triangulateX(&rhand,30,20,10);
	triangulateX(&lhand,30,20,10);
	triangulateX(&rforearm,30,20,10);
	triangulateX(&lforearm,30,20,10);
	triangulateX(&rshoulder,30,20,10);
	triangulateX(&lshoulder,30,20,10);

	triangulateY(&abdomen,30,20,5);
	triangulateY(&head,30,20,10);
	triangulateY(&neck,30,20,10);
	triangulateY(&chest,30,20,10);
	triangulateY(&hip,30,20,5);
	triangulateY(&rcollar,30,20,10);
	triangulateY(&lcollar,30,20,10);
	triangulateY(&rthigh,30,20,10);
	triangulateY(&lthigh,30,20,10);
	triangulateY(&rshin,30,20,10);
	triangulateY(&lshin,30,20,10);

	triangulateZ(&lfoot,30,20,10);
	triangulateZ(&rfoot,30,20,10);
}

int cmpX(const Dot &a, const Dot &b)
{
	if(a.x<b.x)
		return 1;
	else
		return 0;
}
int cmpY(const Dot &a, const Dot &b)
{
	if(a.y<b.y)
		return 1;
	else
		return 0;
}
int cmpZ(const Dot &a, const Dot &b)
{
	if(a.z<b.z)
		return 1;
	else
		return 0;
}

void Body::sortAsClockX(vector<Dot> * currentcircle)
{
	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		//centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = currentcircle->at(0).x;
	centerdot.y = centerdot.y/currentcircle->size();
	centerdot.z = centerdot.z/currentcircle->size();
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownX(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End


}
void Body::sortAsClockY(vector<Dot> * currentcircle)
{
	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		//centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = currentcircle->at(0).y;
	centerdot.z = centerdot.z/currentcircle->size();
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownY(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End


}
void Body::sortAsClockZ(vector<Dot> * currentcircle)
{
	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		//centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = centerdot.z/currentcircle->size();
	centerdot.z = currentcircle->at(0).z;
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownZ(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End


}

void Body::triangulateX(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	//��ĳһ����������
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpX);

	


	//�ֳ�Ȧ
	//����Ӧ�ֵ�Ȧ��=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).x - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).x))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).x;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).x;
	//��Ϊ���������ˣ�����boundary2�ض�����boundary1��boundary2���ң�boundary1����
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).x>=newboundary1 && currentBodyPart->dotCollection.at(i).x<=newboundary2)	
		//���ڴ˲���
		{
			//����һ���㣬��������x��Ȧ�ϣ�����yz�뱾ѭ���ĵ���ͬ
			Dot * tmpdot = new Dot(circlevalue,currentBodyPart->dotCollection.at(i).y,currentBodyPart->dotCollection.at(i).z);
			tmpvector->push_back(*tmpdot);
			//�����ڴ˴�deleteָ��
		}
		//�������һ�㣬�����ƶ�һ��gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//���ƶ�һ��gap��������СֵҪ�󣬲�������һ��
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//�޸��ϲ�[û��min�Ĳ�]��xΪ�²��circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).x = circlevalue;
			}
		}
	}
	
	




	//�����ֵ������Ȧ�е���
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//ɾ������㣬������ĵ�����ȷ�������ɾ
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//��vector��ɾ������ֵ��ǰ��
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//ɾ�����һ��Ԫ��
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//��ÿһȦ���׵����Ϊ�������
	//ȷ����׼��
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//����������
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//��Ȧ�е�ѭ���ҳ�����ĵ�
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//�������ŵ�Ȧ��
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//�޸�ѭ����
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//��ͬһʱ�뷽�������
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		//���һȦ���а�ʱ�뷽�������
		sortAsClockX(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection���������ʷֺõĵ㼯��dotCollection����ԭ�ȵĵ㼯


}
void Body::triangulateY(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpY);
	
	


	//�ֳ�Ȧ
	//����Ӧ�ֵ�Ȧ��=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).y - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).y))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).y;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).y;
	//��Ϊ���������ˣ�����boundary2�ض�����boundary1��boundary2���ң�boundary1����
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).y>=newboundary1 && currentBodyPart->dotCollection.at(i).y<=newboundary2)	
		//���ڴ˲���
		{
			//����һ���㣬��������x��Ȧ�ϣ�����yz�뱾ѭ���ĵ���ͬ
			Dot * tmpdot = new Dot(currentBodyPart->dotCollection.at(i).x,circlevalue,currentBodyPart->dotCollection.at(i).z);
			tmpvector->push_back(*tmpdot);
			//�����ڴ˴�deleteָ��
		}
		//�������һ�㣬�����ƶ�һ��gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//���ƶ�һ��gap��������СֵҪ�󣬲�������һ��
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//�޸��ϲ�[û��min�Ĳ�]��xΪ�²��circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).y = circlevalue;
			}
		}
	}
	
	




	//�����ֵ������Ȧ�е���
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//ɾ������㣬������ĵ�����ȷ�������ɾ
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//��vector��ɾ������ֵ��ǰ��
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//ɾ�����һ��Ԫ��
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//��ÿһȦ���׵����Ϊ�������
	//ȷ����׼��
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//����������
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//��Ȧ�е�ѭ���ҳ�����ĵ�
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//�������ŵ�Ȧ��
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//�޸�ѭ����
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//��ͬһʱ�뷽�������
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		//���һȦ���а�ʱ�뷽�������
		sortAsClockY(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection���������ʷֺõĵ㼯��dotCollection����ԭ�ȵĵ㼯


}
void Body::triangulateZ(BodyPart * currentBodyPart,int max,int min,int circleNum)
{
	sort(currentBodyPart->dotCollection.begin(),currentBodyPart->dotCollection.end(),cmpZ);
	
	


	//�ֳ�Ȧ
	//����Ӧ�ֵ�Ȧ��=circleNum
	float gap = (fabs(currentBodyPart->dotCollection.at(0).z - currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).z))/circleNum;
	float boundary1 =  currentBodyPart->dotCollection.at(0).z;
	float boundary2 =  currentBodyPart->dotCollection.at(currentBodyPart->dotCollection.size()-1).z;
	//��Ϊ���������ˣ�����boundary2�ض�����boundary1��boundary2���ң�boundary1����
	float newboundary1 = boundary1 - gap/2;
	float newboundary2 = boundary1 + gap/2;
	float circlevalue = boundary1;

	vector<Dot> * tmpvector = new vector<Dot>();
	for(int i=0;i<currentBodyPart->dotCollection.size();i++)
	{
		if(currentBodyPart->dotCollection.at(i).z>=newboundary1 && currentBodyPart->dotCollection.at(i).z<=newboundary2)	
		//���ڴ˲���
		{
			//����һ���㣬��������x��Ȧ�ϣ�����yz�뱾ѭ���ĵ���ͬ
			Dot * tmpdot = new Dot(currentBodyPart->dotCollection.at(i).x,currentBodyPart->dotCollection.at(i).y,circlevalue);
			tmpvector->push_back(*tmpdot);
			//�����ڴ˴�deleteָ��
		}
		//�������һ�㣬�����ƶ�һ��gap
		else if((tmpvector->size()) >= min)
		{
			currentBodyPart->circleCollection.push_back(*tmpvector);
			tmpvector = new vector<Dot>();

			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;
		}
		//���ƶ�һ��gap��������СֵҪ�󣬲�������һ��
		else
		{
			newboundary1 = newboundary1 + gap;
	        newboundary2 = newboundary2 + gap;
			circlevalue = circlevalue + gap;

			//�޸��ϲ�[û��min�Ĳ�]��xΪ�²��circlevalue
			for(int j=0;j<tmpvector->size();j++)
			{
				tmpvector->at(j).z = circlevalue;
			}
		}
	}
	
	




	//�����ֵ������Ȧ�е���
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	
	{
		if(currentBodyPart->circleCollection.at(i).size()>max)
		{
			//ɾ������㣬������ĵ�����ȷ�������ɾ
			float deleteNum = currentBodyPart->circleCollection.at(i).size() - max + 1;
			float deleteGap = currentBodyPart->circleCollection.at(i).size()/deleteNum;
			float deleteCurrent = 0.0;
			
			for(int k=deleteNum;k>0;k--)
			{
				deleteCurrent += deleteGap;
				if(deleteCurrent>currentBodyPart->circleCollection.at(i).size())
				{
					deleteCurrent -= currentBodyPart->circleCollection.at(i).size();
				}

				//��vector��ɾ������ֵ��ǰ��
				for(int r=int(deleteCurrent);r<currentBodyPart->circleCollection.at(i).size()-1;r++)
				{
					currentBodyPart->circleCollection.at(i).at(r) = currentBodyPart->circleCollection.at(i).at(r+1);
				}
				//ɾ�����һ��Ԫ��
				currentBodyPart->circleCollection.at(i).pop_back();
			}
		}
	}


	circleNum = currentBodyPart->circleCollection.size();


	//��ÿһȦ���׵����Ϊ�������
	//ȷ����׼��
	Dot datumDot = currentBodyPart->circleCollection.at(0).at(0);
	int nearest = 0;	//����������
	float minest_distance = 0.0;
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		minest_distance = (currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(0).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(0).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(0).z - datumDot.z);

		for(int j=0;j<currentBodyPart->circleCollection.at(i).size();j++)	//��Ȧ�е�ѭ���ҳ�����ĵ�
		{
			if(minest_distance>(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z))
			{
				nearest = j;
				minest_distance = (currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)*(currentBodyPart->circleCollection.at(i).at(j).x - datumDot.x)+(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)*(currentBodyPart->circleCollection.at(i).at(j).y - datumDot.y)+(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z)*(currentBodyPart->circleCollection.at(i).at(j).z - datumDot.z);
			}
		}
		//�������ŵ�Ȧ��
		Dot tmpDot(currentBodyPart->circleCollection.at(i).at(nearest).x,currentBodyPart->circleCollection.at(i).at(nearest).y,currentBodyPart->circleCollection.at(i).at(nearest).z);
		currentBodyPart->circleCollection.at(i).at(nearest).x = currentBodyPart->circleCollection.at(i).at(0).x;
		currentBodyPart->circleCollection.at(i).at(nearest).y = currentBodyPart->circleCollection.at(i).at(0).y;
		currentBodyPart->circleCollection.at(i).at(nearest).z = currentBodyPart->circleCollection.at(i).at(0).z;
		currentBodyPart->circleCollection.at(i).at(0).x = tmpDot.x;
		currentBodyPart->circleCollection.at(i).at(0).y = tmpDot.y;
		currentBodyPart->circleCollection.at(i).at(0).z = tmpDot.z;

		//�޸�ѭ����
		nearest = 0;
		datumDot = currentBodyPart->circleCollection.at(i).at(0);
	}





	//��ͬһʱ�뷽�������
	for(int i=0;i<currentBodyPart->circleCollection.size();i++)	//��Ȧѭ��
	{
		//���һȦ���а�ʱ�뷽�������
		sortAsClockZ(&currentBodyPart->circleCollection.at(i));
	}





	//circleCollection���������ʷֺõĵ㼯��dotCollection����ԭ�ȵĵ㼯


}







void Body::creatSurface()
{
	creatSurfaceX();
	creatSurfaceY();
	creatSurfaceZ();
}

void Body::adjust()
{

}

void Body::creatSurfaceX()
{
	//rhand
	//lhand
	//rforearm
	//lforearm
	//rshoulder
	//lshoulder
	vector<Dot> *circle1 = NULL;
	vector<Dot> *circle2 = NULL;

	//rhand		����
	for(int i = 0; i < rhand.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rhand.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rhand.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		
		creatPartSurfaceX(circle1, circle2, &rhand.surfaceCollection);
	}


	//��������ǰ������	��������ǰ����
	//���ֵ����һ��Ȧ
	circle1 = &rhand.circleCollection.at(rhand.circleCollection.size() - 1);	
	//��ǰ�۵ĵ�һ��Ȧ
	circle2 = &rforearm.circleCollection.at(0);
	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);


	//rforearm		��ǰ��
	for(int i = 0; i < rforearm.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rforearm.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rforearm.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);
	}


	//��ǰ�����Ҽ粿����		��������ǰ��
	//��ǰ�۵����һ��Ȧ
	circle1 = &rforearm.circleCollection.at(rforearm.circleCollection.size() - 1);	
	//�Ҽ粿�ĵ�һ��Ȧ
	circle2 = &rshoulder.circleCollection.at(0);
	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &rforearm.surfaceCollection);

	//rshoulder		�Ҽ粿
	for(int i = 0; i < rshoulder.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rshoulder.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rshoulder.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &rshoulder.surfaceCollection);
	}

	//lshoulder		��粿
	for(int i = 0; i < lshoulder.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lshoulder.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lshoulder.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lshoulder.surfaceCollection);
	}


	//��粿����ǰ������		��������ǰ��
	//��粿�����һ��Ȧ
	circle1 = &lshoulder.circleCollection.at(lshoulder.circleCollection.size() - 1);	
	//��ǰ�۵ĵ�һ��Ȧ
	circle2 = &lforearm.circleCollection.at(0);
	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);


	//lforearm		��ǰ��
	for(int i = 0; i < lforearm.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lforearm.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lforearm.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);
	}


	//��ǰ�������ֵ�����		��������ǰ��
	//��ǰ�۵����һ��Ȧ
	circle1 = &lforearm.circleCollection.at(lforearm.circleCollection.size() - 1);	
	//���ֱ۵ĵ�һ��Ȧ
	circle2 = &lhand.circleCollection.at(0);
	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceX(circle1, circle2, &lforearm.surfaceCollection);


	//lhand		����
	for(int i = 0; i < lhand.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lhand.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lhand.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceX(circle1, circle2, &lhand.surfaceCollection);
	}
}

void Body::creatSurfaceY()
{
	//abdomen	���� �¸�
	//head		ͷ
	//neck		����
	//chest		�ز�
	//hip		�β�
	//rcollar	��Ȧ
	//lcollar	��Ȧ
	//rthigh	����
	//lthigh
	//rshin		С��
	//lshin
	vector<Dot> *circle1 = NULL;	
	vector<Dot> *circle2 = NULL;

	//lshin		��С��
	for(int i = 0; i < lshin.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lshin.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lshin.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lshin.surfaceCollection);
	}


	//��С�������������		��������С��
	//��С�����һ��Ȧ
	circle1 = &lshin.circleCollection.at(lshin.circleCollection.size() - 1);	
	//����ȵĵ�һ��Ȧ
	circle2 = &lthigh.circleCollection.at(0);

	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &lshin.surfaceCollection);


	//lthigh		�����
	for(int i = 0; i < lthigh.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lthigh.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lthigh.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lthigh.surfaceCollection);
	}


	//rshin		��С��
	for(int i = 0; i < rshin.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rshin.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rshin.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rshin.surfaceCollection);
	}


	//��С�����Ҵ�������	��������С��
	//��С�����һ��Ȧ
	circle1 = &rshin.circleCollection.at(rshin.circleCollection.size() - 1);	
	//�Ҵ��ȵĵ�һ��Ȧ
	circle2 = &rthigh.circleCollection.at(0);

	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &rshin.surfaceCollection);


	//rthigh		�Ҵ���
	for(int i = 0; i < rthigh.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rthigh.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rthigh.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rthigh.surfaceCollection);
	}

	
	//hip		�β�
	for(int i = 0; i < hip.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &hip.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &hip.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &hip.surfaceCollection);
	}
	

	//�β���С������		������С��
	//�β����һ��Ȧ
	circle1 = &hip.circleCollection.at(hip.circleCollection.size() - 1);	
	//С���ĵ�һ��Ȧ
	circle2 = &abdomen.circleCollection.at(0);

	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);


	//abdomen	С��
	for(int i = 0; i < abdomen.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &abdomen.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &abdomen.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);
	}


	//С�����ز�����		������С��
	//С�����һ��Ȧ
	circle1 = &abdomen.circleCollection.at(abdomen.circleCollection.size() - 1);	
	//�ز��ĵ�һ��Ȧ
	circle2 = &chest.circleCollection.at(0);

	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &abdomen.surfaceCollection);


	//chest		�ز�
	for(int i = 0; i < chest.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &chest.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &chest.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &chest.surfaceCollection);
	}


	//rcollar
	for(int i = 0; i < rcollar.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &rcollar.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &rcollar.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &rcollar.surfaceCollection);
	}


	//lcollar
	for(int i = 0; i < lcollar.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &lcollar.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &lcollar.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &lcollar.surfaceCollection);
	}


	//neck		����
	for(int i = 0; i < neck.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &neck.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &neck.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &neck.surfaceCollection);
	}

	//������ͷ��������		�����ھ���
	//�������һ��Ȧ
	circle1 = &neck.circleCollection.at(neck.circleCollection.size() - 1);	
	//ͷ���ĵ�һ��Ȧ
	circle2 = &head.circleCollection.at(0);

	//����Surface�����뵽SurfaceCollection
	creatPartSurfaceY(circle1, circle2, &neck.surfaceCollection);

	//head		ͷ��
	for(int i = 0; i < head.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		circle1 = &head.circleCollection.at(i);	
		//�ڶ���Ȧ
		circle2 = &head.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceY(circle1, circle2, &head.surfaceCollection);
	}
}

void Body::creatSurfaceZ()
{
	//lfoot
	for(int i = 0; i < lfoot.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		vector<Dot> *circle1 = &lfoot.circleCollection.at(i);	
		//�ڶ���Ȧ
		vector<Dot> *circle2 = &lfoot.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceZ(circle1, circle2, &lfoot.surfaceCollection);
	}

	//rfoot
	for(int i = 0; i < rfoot.circleCollection.size() - 1; i++)
	{
		//��һ��Ȧ
		vector<Dot> *circle1 = &rfoot.circleCollection.at(i);	
		//�ڶ���Ȧ
		vector<Dot> *circle2 = &rfoot.circleCollection.at(i + 1);

		//����Surface�����뵽SurfaceCollection
		creatPartSurfaceZ(circle1, circle2, &rfoot.surfaceCollection);
	}
}

/*****************************************************
 *��circle1 �� circle2 �����ݴ���Surface �����뵽SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceX(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////�˴����ִ���

	vector<float> tempArc1 = vector<float>();											//�Ƕ�1
	vector<float> tempArc2 = vector<float>();											//�Ƕ�2

	//����Ƕ�1
	calculArcX(circle1, tempArc1);
	//����Ƕ�2
	calculArcX(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//�����Ƕ�����������
	int p1 = 0;			//Ȧ1 ��ָʾ ָ����һ��δʹ�õĵ�
	int p2 = 0;			//Ȧ2 ��ָʾ
	int arc1 = 1;		//�Ƕ�1 �е�ָʾ ָ����һ��δ�õĽǶ�
	int arc2 = 1;
	Dot A;				//�����ε������� A  B  C
	Dot B;
	Dot C;
	
	//����Ȧ�������ݵĲ���
	//ȡ��һ�ڶ�����
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//ȡ��������
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//Ϊ��һ��ȡ����׼��
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//����Ȧֻ��һ��Ȧ�����ݵĲ���
	if((arc1 >= tempArc1.size() - 1))
	{
		//ʣ�µ�ֻ��circle2������
		//A C ����circle1��
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//���һ��Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//���һ�� p1���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//ʣ�µ�ֻ��circle1��������
		//B C ����circle2��
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//���һ��Surface
		C = circle2->at(p2);			//���һ�� p2���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

/*****************************************************
 *��circle1 �� circle2 �����ݴ���Surface �����뵽SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceY(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////�˴����ִ���

	vector<float> tempArc1 = vector<float>();											//�Ƕ�1
	vector<float> tempArc2 = vector<float>();											//�Ƕ�2

	//����Ƕ�1
	calculArcY(circle1, tempArc1);
	//����Ƕ�2
	calculArcY(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//�����Ƕ�����������
	int p1 = 0;			//Ȧ1 ��ָʾ ָ����һ��δʹ�õĵ�
	int p2 = 0;			//Ȧ2 ��ָʾ
	int arc1 = 1;		//�Ƕ�1 �е�ָʾ ָ����һ��δ�õĽǶ�
	int arc2 = 1;
	Dot A;				//�����ε������� A  B  C
	Dot B;
	Dot C;
	
	//����Ȧ�������ݵĲ���
	//ȡ��һ�ڶ�����
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//ȡ��������
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//Ϊ��һ��ȡ����׼��
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//����Ȧֻ��һ��Ȧ�����ݵĲ���
	if((arc1 >= tempArc1.size() - 1))
	{
		//ʣ�µ�ֻ��circle2������
		//A C ����circle1��
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//���һ��Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//���һ�� p1���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//ʣ�µ�ֻ��circle1��������
		//B C ����circle2��
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//���һ��Surface
		C = circle2->at(p2);			//���һ�� p2���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

/*****************************************************
 *��circle1 �� circle2 �����ݴ���Surface �����뵽SurfaceCollection
 ****************************************************/
void Body::creatPartSurfaceZ(vector<Dot> *circle1, vector<Dot> *circle2, vector<Surface> *surfaceCollection)
{
	if( !circle1 || !circle2)
		return;             ////////////////////////////�˴����ִ���

	vector<float> tempArc1 = vector<float>();											//�Ƕ�1
	vector<float> tempArc2 = vector<float>();											//�Ƕ�2

	//����Ƕ�1
	calculArcZ(circle1, tempArc1);
	//����Ƕ�2
	calculArcZ(circle2, tempArc2);

	//int minNum = tempArc1.size() <= tempArc2.size() ? tempArc1.size() : tempArc2.size();	//�����Ƕ�����������
	int p1 = 0;			//Ȧ1 ��ָʾ ָ����һ��δʹ�õĵ�
	int p2 = 0;			//Ȧ2 ��ָʾ
	int arc1 = 1;		//�Ƕ�1 �е�ָʾ ָ����һ��δ�õĽǶ�
	int arc2 = 1;
	Dot A;				//�����ε������� A  B  C
	Dot B;
	Dot C;
	
	//����Ȧ�������ݵĲ���
	//ȡ��һ�ڶ�����
	A = circle1->at(p1);	p1++;
	B = circle2->at(p2);	p2++;
	while((arc1 < tempArc1.size() - 1) && (arc2 < tempArc2.size() - 1))
	{
		bool inOne = true;
		
		//ȡ��������
		if(tempArc1.at(arc1) >= tempArc2.at(arc2))
		{
			C = circle1->at(p1); p1++;
			inOne = true;
			arc1++;
		}
		else
		{
			C = circle2->at(p2); p2++;
			inOne = false;
			arc2++;
		}
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);

		//Ϊ��һ��ȡ����׼��
		if(inOne)
		{
			A = C;
		}
		else
		{
			B = C;
		}
	}
	
	//����Ȧֻ��һ��Ȧ�����ݵĲ���
	if((arc1 >= tempArc1.size() - 1))
	{
		//ʣ�µ�ֻ��circle2������
		//A C ����circle1��
		A = C;
		while(p2 < circle2->size())
		{
			C = B;
			B = circle2->at(p2);	p2++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);

		}
		//���һ��Surface
		C = circle1->at(p1);///*circle1->size() - 1*/);		//���һ�� p1���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}else
	{
		//ʣ�µ�ֻ��circle1��������
		//B C ����circle2��
		B = C;
		while(p1 < circle1->size())
		{
			C = A;
			A = circle1->at(p1);	p1++;
			//����Surface
			Surface creatSur = Surface(A, B, C);
			surfaceCollection->push_back(creatSur);
		}
		//���һ��Surface
		C = circle2->at(p2);			//���һ�� p2���Բ�����
		//����Surface
		Surface creatSur = Surface(A, B, C);
		surfaceCollection->push_back(creatSur);
	}
}

void Body::calculArcX(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//�����������

	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		//centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = currentcircle->at(0).x;
	centerdot.y = centerdot.y/currentcircle->size();
	centerdot.z = centerdot.z/currentcircle->size();
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	//vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownX(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End

}

void Body::calculArcY(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//�����������

	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		//centerdot.y = centerdot.y + currentcircle->at(k).y;
		centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = currentcircle->at(0).y;
	centerdot.z = centerdot.z/currentcircle->size();
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	//vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownY(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End

}

void Body::calculArcZ(vector<Dot> * currentcircle, vector<float> &center_arc)
{
	if( !currentcircle)
		return;					//�����������

	//ȷ�����ĵ� Start
	Dot centerdot(0.0,0.0,0.0);
	for(int k=0;k<currentcircle->size();k++)
	{
		centerdot.x = centerdot.x + currentcircle->at(k).x;
		centerdot.y = centerdot.y + currentcircle->at(k).y;
		//centerdot.z = centerdot.z + currentcircle->at(k).z;
	}
	centerdot.x = centerdot.x/currentcircle->size();
	centerdot.y = centerdot.z/currentcircle->size();
	centerdot.z = currentcircle->at(0).z;
	//ȷ�����ĵ� End


	//ȷ���׵�
	Dot firstDot1 = Dot(currentcircle->at(0).x,currentcircle->at(0).y,currentcircle->at(0).z);
	//ȷ��������
	Dot datumvector1 = Dot(currentcircle->at(0).x-centerdot.x,currentcircle->at(0).y-centerdot.y,currentcircle->at(0).z-centerdot.z);
	//ȷ���׵�Ķ�Ӧ��
	Dot firstDot2 = CalculateCorrespondDot(firstDot1,centerdot);
	//ȷ���׵�Ķ�Ӧ�������
	Dot datumvector2 = Dot(firstDot2.x-centerdot.x,firstDot2.y-centerdot.y,firstDot2.z-centerdot.z);


	//ȷ����Ӧ�Ĵ����ĵ㷢�������� Start
	vector<Dot> center_vector;
	for(int k=0;k<currentcircle->size();k++)
	{
		Dot *tmpDot = new Dot(currentcircle->at(k).x-centerdot.x,currentcircle->at(k).y-centerdot.y,currentcircle->at(k).z-centerdot.z);
		center_vector.push_back(*tmpDot);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢�������� End


	//vector<float> center_arc;	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ Start

	for(int k=0;k<currentcircle->size();k++)
	{
		float tmparc;
		if( UpOrDownZ(firstDot1,firstDot2,currentcircle->at(k)) ==1)		//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector1) + 2;
		}
		else	//����
		{
			tmparc = CalculateVectorCos(center_vector.at(k),datumvector2);
		}

		center_arc.push_back(tmparc);
	}
	//ȷ����Ӧ�Ĵ����ĵ㷢����������ĽǶȵ�cosֵ End



	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� Start
	

	//ð�����򣬴�����ǰ��С���ں�ÿһ�ֽ���СԪ���������
	for(int i=0;i<center_arc.size()-1;i++)	//ÿһ�ֵ�ѭ��
	{
		for(int j=0;j<center_arc.size()-i-1;j++)	//ÿ���еĶ����߱Ƚϵ�ѭ��
		{
			//��С�����໻
			if(center_arc.at(j)<center_arc.at(j+1))
			{
				float tmparc = 0.0;
				Dot tmpdot = Dot(0.0,0.0,0.0);
				tmparc = center_arc.at(j+1);
				center_arc.at(j+1) = center_arc.at(j);
				center_arc.at(j) = tmparc;
				tmpdot = currentcircle->at(j);
				currentcircle->at(j) = currentcircle->at(j+1);
				currentcircle->at(j+1) = tmpdot;
			}
		}
	}


	//����center_arc����Ӧ��ֵ��cosֵ�Ӹߵ��ͣ����ǣ������׼��˳ʱ��Ĵ�Զ���� End


}