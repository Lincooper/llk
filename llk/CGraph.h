#pragma once
#ifndef CGRAPH_H
#define CGRAPH_H
#include"global.h"

class CGraph
{
public:
	CGraph();
	~CGraph(void);
	void InitGraph();
	void ClearGraph(void);							//清理图结构
	void AddArc(int nV1Index, int nV2Index);		//添加生成边		
	bool GetArc(int nV1Index, int nV2Index);		//获得两个顶点的边
	int GetVertex(int nIndex);						//获取顶点索引号
	int AddVertex(int nInfo);						//添加顶点，并获得顶点个数
	void UpdateVertex(int nIndex, int info);		//更新顶点信息，将图顶点数组中索引号为nIndex的顶点的值更新为info
	int GetVexnum();								//获取图中顶点的个数
	void ChangeVerex(int nIndex1, int nIndex2);		//调换两个点的位置

protected:
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjHatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	Vertices	m_Vertices;		// 一维数组 顶点数组 保存顶点
	AdjHatrix	m_AdjMatrix;	//二维数组  关系矩阵 保存两顶点间的边
	int			m_nVexnum;		//顶点数
	int			m_nArcnum;		// 边数
};
#endif // !CGRAPH_H
