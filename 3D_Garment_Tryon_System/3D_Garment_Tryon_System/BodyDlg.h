#pragma once

#include "Display.h"
#include "Body.h"

// CBodyDlg �Ի���

class CBodyDlg : public CDialogEx
{

	DECLARE_EASYSIZE

	DECLARE_DYNAMIC(CBodyDlg)

public:
	CBodyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBodyDlg();

// �Ի�������
	enum { IDD = IDD_BODYTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()



// ʵ��
public:

	//���ӵĳ�Ա����
	Display *displayBody;		//��ͼ����
	CRect	m_rect;				//��ͼ����
	int		m_bodyRecord;			//��ͼ��¼
	int		m_bodyBG;				//������¼
	bool	m_isClear;				//�ж��Ƿ����

	//int		m_nHitTest;


	//body����
	Body *body;
	//�Ӹ��Ի��򴫵����ɵ�body
	void setBody(Body *tmpBody);

	void Redraw();



public:
	afx_msg void OnBnClickedBodystartbut();
	afx_msg void OnBnClickedBodysimplybut();
	afx_msg void OnBnClickedBodycompletebut();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider6(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_XSlider;
	CSliderCtrl m_ZSlider;
	CSliderCtrl m_YSlider;
	CComboBox m_ChangeBG;
	virtual BOOL OnInitDialog();
	CSliderCtrl m_HeightSlider;
	CSliderCtrl m_ChestSlider;
	CSliderCtrl m_WaistSlider;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
