#pragma once
#ifndef CSETTINGDLG_H
#define CSETTINGDLG_H


#include "afxdialogex.h"


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DIALOG };
#endif

protected:
	HICON m_hIcon;    //系统图片
	CDC m_dcMem;      //内存DC
	CDC m_dcSet;     //帮助图片DC
	CRect m_rtSet;   //帮助图片显示区域
	static CString SetPath;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitSetting();
	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();
	
	void SetTheme(int theme);
	void SetMap(int row, int col, int picNum);
	void SetBGM(bool musicOn);
	bool IsNum(CString s);
	bool musicOn;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRadioClose();
	afx_msg void OnBnClickedRadioOpen();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeComboTheme();
};
#endif // !CSETTINGDLG_H