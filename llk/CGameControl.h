#pragma once
#ifndef CGAMECONTROL_H
#define CGAMECONTROL_H



#include "afxdialogex.h"
#include"CGameLogic.h"



// CGameControl 对话框

class CGameControl : public CDialogEx
{
	DECLARE_DYNAMIC(CGameControl)

public:
	CGameControl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameControl();

	CGraph m_graph;		//初始地图为4行4列
	Vertex selFirst;	//选择的第一个点
	Vertex selSecond;	//选择的第二个点

	CGameLogic m_GameLogic;//实现具体逻辑

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int GetElement(int nRow, int nCol);//获取图中数据
	int StartGame(int rows, int cols, int picNum);//开始游戏，供CGameDlg类调用

	void SetFirstPoint(int nRow, int nCol);
	void SetSecondPoint(int nRow, int nCol);
	void ClearMap();


	//bool Link(stack<Vertex>& verList);//判断selFirst和selSecond是否相连，相连路径放verList中
	bool Link(Vertex avPath[], int& nVexnum);//判断selFirst和selSecond是否相连，相连路径放verList中
	bool isWin();                     //判断游戏是否结束

	//帮助、提示方法
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);

	//实现重排功能
	void Reset(void);

	afx_msg void OnNMCustomdrawPrbTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditTime();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
};

#endif // !CGAMECONTROL_H


