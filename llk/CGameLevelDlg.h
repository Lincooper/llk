#pragma once
#ifndef CGAMELEVELDLG_H
#define CGAMELEVELDLG_H


#include "afxdialogex.h"


// CGameLevelDlg 对话框

class CGameLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLevelDlg)

public:
	CGameLevelDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameLevelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEVEL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;		//系统图标
	CDC m_dcMem;		//内存DC
	CDC m_dcLevel;			//背景
	static CString LevelPath;
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	void SetLevel(int level);
	void InitBackground();

	afx_msg void OnBnClickedEasyButton();
	afx_msg void OnBnClickedNormalButton();
	afx_msg void OnBnClickedHardButton();
	afx_msg void OnPaint();
};
#endif // !CGAMELEVELDLG_H