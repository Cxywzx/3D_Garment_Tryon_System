
// 3D_Garment_Tryon_SystemDlg.h : ͷ�ļ�
//



#pragma once


#include "GarmentDlg.h"
#include "BodyDlg.h"

#include "Body.h"
//#include "NetGrid.h"
#include "Garment.h"

// CMy3D_Garment_Tryon_SystemDlg �Ի���
class CMy3D_Garment_Tryon_SystemDlg : public CDialogEx
{
	DECLARE_EASYSIZE
// ����
public:
	CMy3D_Garment_Tryon_SystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY3D_GARMENT_TRYON_SYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CBodyDlg bodydlg;
	CGarmentDlg garmentdlg;

	HICON m_hIcon;

	//����湲�ж���
	Body	*body;//����
	NetGrid *netGrid;//����


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabModel;
	afx_msg void OnTcnSelchangeModeltab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
