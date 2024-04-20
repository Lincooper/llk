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
	void ClearGraph(void);							//����ͼ�ṹ
	void AddArc(int nV1Index, int nV2Index);		//������ɱ�		
	bool GetArc(int nV1Index, int nV2Index);		//�����������ı�
	int GetVertex(int nIndex);						//��ȡ����������
	int AddVertex(int nInfo);						//��Ӷ��㣬����ö������
	void UpdateVertex(int nIndex, int info);		//���¶�����Ϣ����ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
	int GetVexnum();								//��ȡͼ�ж���ĸ���
	void ChangeVerex(int nIndex1, int nIndex2);		//�����������λ��

protected:
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjHatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	Vertices	m_Vertices;		// һά���� �������� ���涥��
	AdjHatrix	m_AdjMatrix;	//��ά����  ��ϵ���� �����������ı�
	int			m_nVexnum;		//������
	int			m_nArcnum;		// ����
};
#endif // !CGRAPH_H
