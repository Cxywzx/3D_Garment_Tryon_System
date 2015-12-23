#pragma once

#include "Display.h"
#include "Garment.h"




// CGarmentDlg �Ի���

class CGarmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGarmentDlg)

public:
	CGarmentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGarmentDlg();

// �Ի�������
	enum { IDD = IDD_GARMENTTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


// ʵ��
public:

	//���ӵĳ�Ա����
	Display *displayGarment;		//��ͼ����
	CRect	m_rect;					//��ͼ����
	int		m_garmentRecord;			//��ͼ��¼
	int		m_garmentBG;			//������¼
	bool	m_isClear;				//�Ƿ����
	
	//�·�����
	Garment *garment;
	//body����
	Body *body;
	//�Ӹ��Ի��򴫵����ɵ�body
	void setBody(Body *tmpBody);

	//�������
	NetGrid *netGrid;
	//�Ӹ��Ի��򴫵����ɵ�netgrid
	void setNetGrid(NetGrid *tmpNetGrid);

	//BoxCloth boxCloth;


	void Redraw();

public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CSliderCtrl m_XSlider;
	CSliderCtrl m_YSlider;
	CSliderCtrl m_ZSlider;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_ChangeBG;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
