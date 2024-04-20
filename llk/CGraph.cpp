#include "pch.h"
#include "CGraph.h"
#include "ParamSetting.h"

CGraph::CGraph()
{
	InitGraph();
}

CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	m_nVexnum = 0;
	m_nArcnum = 0;
	/*int num = ParamSetting::rows * ParamSetting::cols;*/
	// 初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;	
	}
	// 初始化边
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}

void CGraph::ClearGraph(void)
{
	InitGraph();
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}



int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

int CGraph::AddVertex(int nInfo)
{
	/*int num = ParamSetting::rows * ParamSetting::cols;*/
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

int CGraph::GetVexnum()
{
	return m_nVexnum;
}

void CGraph::ChangeVerex(int nIndex1, int nIndex2)
{
	int Temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = Temp;
}
