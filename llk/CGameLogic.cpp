// CGameLogic.cpp: 实现文件
// 用来实现业务逻辑操作，设计良好的数据结构，并基于此结构完成具体的功能。


#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CGameLogic.h"
#include "ParamSetting.h"


// CGameLogic 对话框

IMPLEMENT_DYNAMIC(CGameLogic, CDialogEx)

CGameLogic::CGameLogic(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	/*int num = ParamSetting::rows;*/
	/*for (int i = 0; i < 4; i++)
	{
		m_avPath[i].col = 0;
		m_avPath[i].row = 0;
		m_avPath[i].info = 0;
	}*/

	m_nVexNum = 0;     //数组中实际元素的个数
	m_nCorner = 0;     //路径中的拐点数
}

CGameLogic::~CGameLogic(void)
{
	
}

//int CGameLogic::GetElem(int nRow, int nCol)
//{
//	//return GameMap[nRow][nCol];
//	return 1;
//}

void CGameLogic::InitMap(CGraph& m_graph)
{
	//固定地图
	//// 初始化图结构
	//int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };

	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		m_graph.AddVertex(anTemp[i][j]);
	//		//UpdateArc(m_graph, i, j);
	//	}
	//}	

	////初始化边
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		UpdateArc(m_graph, i, j);
	//	}
	//}
	//初始化边后，得到的邻接矩阵并不是所有相同边都有联系	
	
	
	//随机生成地图
	/*ParamSetting::rows;
	ParamSetting::cols;
	int picnum = ParamSetting::picNum;
	int num = ParamSetting::rows * ParamSetting::cols;*/
	/*int* anTemp = new int[num];*/
	//int nRepeatNum = (ParamSetting::rows * ParamSetting::cols) / ParamSetting::picNum;
	int anTemp[MAX_VERTEX_NUM];
	
	int nRepeatNum = (Rows * Cols) / PicNum;
	//多少花色
	for (int i = 0; i < PicNum; i++)
	{
		//重复数
		for (int j = 0; j < nRepeatNum; j++)
		{
			anTemp[i * nRepeatNum + j] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	for (int i = 0; i < 300; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int nTemp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTemp;
	}

	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_graph.AddVertex(anTemp[i]);
	}

	//更新弧信息
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			UpdateArc(m_graph, i, j);
		}
	}



	//// 为二维数组开辟空间
	//this->GameMap = new int* [nRows];
	//for (int i = 0; i < nRows; i++) {
	//	GameMap[i] = new int[nCols];
	//	memset(GameMap[i], NULL, sizeof(int) * nCols);

	//}
	////用图片编号填充地图
	//int nRepeatNum = (nRows * nCols) / nPicNum;
	//int nCount = 0;
	//for (int i = 0; i < nPicNum; i++) {
	//	for (int j = 0; j < nRepeatNum; j++) {
	//		GameMap[nCount / nCols][nCount % nCols] = i;
	//		nCount++;
	//	}
	//}
	////将图片陋机打乱
	//srand((int)time(NULL));
	//int nVertexNum = nRows * nCols;
	//for (int i = 0; i < nVertexNum; i++) {
	//	int nIndexl = rand() % nVertexNum;
	//	int nIndex2 = rand() % nVertexNum;
	//	//两个下表交换
	//	int nTmp = GameMap[nIndexl / nCols][nIndexl % nCols];
	//	GameMap[nIndexl / nCols][nIndexl % nCols] = GameMap[nIndex2 / nCols][nIndex2 % nCols];
	//	GameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	//}
}



void CGameLogic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameLogic, CDialogEx)
END_MESSAGE_MAP()


// CGameLogic 消息处理程序







//判断所有的图片是否已经清除
bool CGameLogic::isBlank(CGraph& m_graph)
{
	int nVexnum = m_graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		if (m_graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	m_graph.InitGraph();
	return true;

	/*for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Cols; j++) {
			if (this->GameMap[i][j] != BLANK) {
				return false;
			}
		}
	}
	return true;*/
}

void CGameLogic::UpdateArc(CGraph& m_graph, int nRow, int nCol)
{
	//设置每个点的序号
	int nIndex1 = nRow * Cols + nCol;
	int nInfo1;
	int nInfo2;

	//构建邻接矩阵
	//若不是第一列
	if (nCol > 0) {
		int nIndex2 = nIndex1 - 1;
		//TODO:判断与左边相邻的是否有关
		nInfo1 = m_graph.GetVertex(nIndex1);
		nInfo2 = m_graph.GetVertex(nIndex2);
		//设 空点 与 任何点 都有联系 是为了后续判断拐点是否为空（即是否能连接）
		if ((nInfo2 == nInfo1) || nInfo1 == BLANK || nInfo2 == BLANK) {
			m_graph.AddArc(nIndex1, nIndex2);
		}
	}

	//若不是第四列
	if (nCol < Cols-1) {
		int nIndex2 = nIndex1 + 1;
		//TODO:判断与右边相邻的是否有关系
		nInfo1 = m_graph.GetVertex(nIndex1);
		nInfo2 = m_graph.GetVertex(nIndex2);
		if ((nInfo2 == nInfo1) || nInfo1 == BLANK || nInfo2 == BLANK) {
			m_graph.AddArc(nIndex1, nIndex2);
		}

	}
	//若不是第一行
	if (nRow > 0) {
		int nIndex2 = nIndex1 - Cols;
		//TODO:判断与正上方的是否有关
		nInfo1 = m_graph.GetVertex(nIndex1);
		nInfo2 = m_graph.GetVertex(nIndex2);
		if ((nInfo2 == nInfo1) || nInfo1 == BLANK || nInfo2 == BLANK) {
			m_graph.AddArc(nIndex1, nIndex2);
		}
	}
	//若不是第四行
	if (nRow < Rows-1) {
		int nIndex2 = nIndex1 + Cols;
		//TODO:判断与正下方的是否有关系
		nInfo1 = m_graph.GetVertex(nIndex1);
		nInfo2 = m_graph.GetVertex(nIndex2);
		if ((nInfo2 == nInfo1) || nInfo1 == BLANK || nInfo2 == BLANK) {
			m_graph.AddArc(nIndex1, nIndex2);
		}
	}
}

bool CGameLogic::IsLink(CGraph& m_graph, Vertex V1, Vertex V2)
{

	//获得顶点索引号
	int nV1Index = V1.row * Cols + V1.col;
	int nV2Index = V2.row * Cols + V2.col;

	//边界点的消除没有做
	// 
	// 
	// 
	//TODO:加入边界外的点做拐点


	PushVertex(nV1Index);  //压入第一个点

	//搜寻两点之间的连通路径
	if (SearchPath(m_graph, nV1Index, nV2Index) == true) {
		//若连通，则将栈内点全部弹出
		/*while (m_nVexNum) {
			PopVertex();
		}*/
		return true;
	}
	PopVertex();
	
	return false;
}

void CGameLogic::Clear(CGraph& m_graph, Vertex V1, Vertex V2)
{
	//获取顶点索引号
	int nV1Index = V1.row * Cols + V1.col;
	int nV2Index = V2.row * Cols + V2.col;

	//更新顶点
	m_graph.UpdateVertex(nV1Index, BLANK);
	m_graph.UpdateVertex(nV2Index, BLANK);
	
	//将消去的点赋值为-1
	//更新边信息
	UpdateArc(m_graph, V1.row, V1.col);
	UpdateArc(m_graph, V2.row, V2.col);
}

bool CGameLogic::SearchPath(CGraph& m_graph, int nV0, int nV1)
{
	//得到顶点数
	int nVexnum = m_graph.GetVexnum();

	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++) {
		if (m_graph.GetArc(nV0, nVi) && !IsExsit(nVi)) {

			//压入当前顶点，假设为路径的一个有效顶点
			PushVertex(nVi);

			//当拐点数大于2 时，直接放弃该顶点
			if (m_nCorner > 2) {
				PopVertex();      //取出压入的顶点
				continue;
			}
			//当前顶点不是nVi时，继续搜寻下一个相邻且连通的顶点
			if (nVi != nV1) {
				//当中间顶点不为空时，表示该条路径不通
				if (m_graph.GetVertex(nVi) != BLANK) {
					PopVertex();    //取出压入的顶点
					continue;
				}
				//如果nVi是一个已消除的点，则判断（nVi，nV1）是否连通
				if (SearchPath(m_graph, nVi, nV1)) {
					return true;
				}
			}
			else {

				return true;
			}
			PopVertex();		//取出压入的顶点
			//PopVertex();			
		}
	}
	return false;
}

bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi)
		{
			return true;
		}
	}
	return false;
}

bool CGameLogic::IsCornor(void)
{
	//大于等于3个顶点
	if (m_nVexNum >= 3)
	{
		//m_anPath保存在进行连接判断时所经过的顶点
		// m_nVexNum - 1为最后一个点 
		//m_nVexNum - 3为第一个点
		// m_nVexNum - 2为中点
		//中点坐标不等于这个顶点的坐标，说明这三个点没有在同一直线上，形成了拐角
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}

void CGameLogic::PushVertex(int v)
{
	//将顶点压栈
	m_anPath[m_nVexNum] = v;
	m_nVexNum++;

	//判断是否形成新的拐点
	if (IsCornor())
	{
		m_nCorner++;
	}
}

void CGameLogic::PopVertex()
{
	
	//判断是否形成拐点，如果存在拐点，在取出之前减少拐点数
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
	//m_anPath[m_nVexNum] = NULL;
}

int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < Cols; point.col++)
		{
			for (point.row = 0; point.row < Rows; point.row++)
			{
				if (point.row * Cols + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}

	return m_nVexNum;
}

bool CGameLogic::SearchValidPath(CGraph& m_graph)
{
	return false;
}

void CGameLogic::ResetGraph(CGraph& m_graph)
{
	/*int num = ParamSetting::rows * ParamSetting::cols;*/
	//随机交换顶点数组中两个顶点的值
	for (int i = 0; i < 200; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		m_graph.ChangeVerex(nIndex1, nIndex2);
	}

	//更新弧信息
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			UpdateArc(m_graph, i, j);
		}
	}
}


//将堆栈verList的信息拷贝给copyList
stack<Vertex>CGameLogic::GetVerList()
{
	stack<Vertex>copyList = stack<Vertex>(verList);
	return copyList;
}



//清空堆栈操作，C++没有提供函数，因此编写函数
void CGameLogic::ClearVerList()
{//利用swap操作比比pop快2/3
	stack<Vertex>().swap(verList);
}

void CGameLogic::ClearMap()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; i++) {
			GameMap[i][j] = BLANK;
		}
	}
}
