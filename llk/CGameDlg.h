#pragma once
#ifndef CGAMEDLG_H
#define CGAMEDLG_H



#include "afxdialogex.h"
#include "CGameControl.h"
#include<mmsystem.h>
#include "ParamSetting.h"
#pragma comment(lib,"winmm.lib")


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
private:
	int GameMode;//表示游戏模式
	CPoint m_GameRegionTop;    //窗体地图左上角图标
	CSize m_sizeElem;          //每个图片的大小
	CRect m_GameRegion;        //地图所在的矩形框

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;		//系统图标
	CDC m_dcMem;		//内存DC
	CDC m_dcBG;			//背景
	CDC m_dcEle;		//元素
	CDC m_dcMask;		//掩码
	CDC m_dcCache;			//掩盖游戏地图
	//static CString BGPath;//背景图片路径
	//static CString ElementPath;//元素图片路径
	//static CString MaskPath;//掩码图片路径
	static CString path;
	
	//创建一个CGameControl对象
	CGameControl m_GameC;
	bool playing;  //游戏是否进行中
	bool pause;	   //是否暂停
	bool firstSelect;//true 表示prepared for第一个点

	CProgressCtrl GameProgress;	//创造一个时间滚动条
	int TimeCount;				//创建一个时间量

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	void InitBackground();
	void SetGameMode(int mode);
	void InitMode(int mode);
	void SetButton(bool start, bool stop, bool prompt, bool reset);
	void InitElement(CString ElementPath, CString MaskPath);
	void UpdateMap();
	void SetGameProgress(int range);
	void TurnonBGMusic(CString Path);
	void TurnoffBGMusic();
	void OnClose();

	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnPrompt();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//鼠标左键松开事件

private:
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(stack<Vertex>verList);
	void DrawTipLine1(Vertex avPath[MAX_VERTEX_NUM], int nVexnum);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#endif // !CGAMEDLG_H