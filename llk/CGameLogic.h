#pragma once
#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H


#include "afxdialogex.h"
#include "global.h"
#include<stack>
#include"CGraph.h"
using namespace std;


// CGameLogic 对话框

class CGameLogic : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLogic)

public:
	CGameLogic(CWnd* pParent = nullptr);   // 标准构造函数
	~CGameLogic();
	//virtual ~CGameLogic();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
private:
	stack<Vertex> verList; //用于保存两个图片相连的路径
public:
	//所需要用到的数据结构

	int** GameMap;//地图信息
	int rows;//地图行
	int cols;//地图列
	int picNum;//地图包含的图片的个数

	
	//int GetElem(int nRow, int nCo1);
	//void InitMap(int nRows, int nCols, int nPicNum);//相当于对Gamewap进行初始化
	void InitMap(CGraph& m_graph);//相当于对Gamewap进行初始化

	
	
	void ClearVerList();
	void ClearMap();
	stack<Vertex>GetVerList();
	bool isBlank(CGraph& m_graph);

	void UpdateArc(CGraph& m_graph, int nRow, int nCol);				//判断游戏地图中的nRow行、nCol列的顶点与它上下左右的顶点是否有边，如果有边，则更新图结构
	bool IsLink(CGraph& m_graph, Vertex V1, Vertex V2);
	void Clear(CGraph& m_graph, Vertex V1, Vertex V2);
	bool SearchPath(CGraph& m_graph, int nV0, int nV1);
	bool IsExsit(int nVi);											//判断顶点是否已在路径中存在
	bool IsCornor(void);											//判断拐点的有效性
	void PushVertex(int v);
	void PopVertex();
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);

	bool SearchValidPath(CGraph& graph);//提示
	void ResetGraph(CGraph& graph);//图结构重排
	

private:



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	Vertex m_avPath[4];    //保存连接路径的起始点、拐点、终点
	int m_nVexNum;         //表示顶点数
	int m_anPath[16];      //保存在进行连接判断时所经过的顶点
	int m_nCorner;         //保存路径中的拐点数
	DECLARE_MESSAGE_MAP()
};
#endif // !CGAMELOGIC_H