
// 3D_Garment_Tryon_System.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy3D_Garment_Tryon_SystemApp:
// �йش����ʵ�֣������ 3D_Garment_Tryon_System.cpp
//

class CMy3D_Garment_Tryon_SystemApp : public CWinApp
{
public:
	CMy3D_Garment_Tryon_SystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy3D_Garment_Tryon_SystemApp theApp;