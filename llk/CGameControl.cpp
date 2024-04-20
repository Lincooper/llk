// CGameControl.cpp: 实现文件
// 用来实现业务控制操作，
// 针对用户发起的事件比如开始游戏，暂停游戏，重排等做出具体的响应。

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CGameControl.h"


// CGameControl 对话框

IMPLEMENT_DYNAMIC(CGameControl, CDialogEx)

CGameControl::CGameControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

}

CGameControl::~CGameControl()
{
}

void CGameControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	int Index = nRow * Cols + nCol;
	return m_graph.GetVertex(Index);
}	

int CGameControl::StartGame(int rows, int cols, int picNum)
{
	// 首先判断3个参数是否合理 不合理返回false
	// 进行地图初始化，填充m_pGameMap 返回true
	if ((rows * cols) % (picNum * 2) != 0) {
		return false;
	}
	else {
		//m_GameLogic.InitMap(rows, cols, picNum);
		m_GameLogic.InitMap(m_graph);
	}
	return true;
	
}




BEGIN_MESSAGE_MAP(CGameControl, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PRB_TIME, &CGameControl::OnNMCustomdrawPrbTime)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CGameControl::OnEnChangeEditTime)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameControl::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_START, &CGameControl::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGameControl::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CGameControl 消息处理程序


//设置第一个点
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	selFirst.row = nRow;
	selFirst.col = nCol;
}


//设置第二个点
void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	selSecond.row = nRow;
	selSecond.col = nCol;
}

void CGameControl::ClearMap()
{
	m_GameLogic.ClearMap();
}


////判断两个点是否相连
//bool CGameControl::Link(stack<Vertex>& verList)
//{
//	//如果相连
//	if (m_GameLogic.IsLink(selFirst, selSecond))
//	{
//		//确定两个图片相连，清空图片，并返回相连路径
//		m_GameLogic.Clear(selFirst, selSecond);
//		verList = m_GameLogic.GetVerList();
//		return true;
//		
//	}
//	return false;
//}


bool CGameControl::Link(Vertex avPath[], int& nVexnum)
{
	// 判断是否为同一个元素
	if ((selFirst.row == selSecond.row) && (selFirst.col == selSecond.col)) {
		return false;

	}
	// 判断元素是否相同
	// 尽写这些bug 两个都是selFirst 不能消才怪
	// 但有个奇怪的现象 相邻不同色不能消 但拐角不同色却能消
	// 终于找到原因 在IsLink（）函数里
	//if ((m_graph.GetVertex(selFirst.row * 4 + selFirst.col) != (m_graph.GetVertex(selFirst.row * 4 + selFirst.col)))) {
	
	int	nInfo1 = m_graph.GetVertex(selFirst.row * Rows + selFirst.col);
	int	nInfo2 = m_graph.GetVertex(selSecond.row * Cols + selSecond.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}
	/*if ((m_graph.GetVertex(selFirst.row * 4 + selFirst.col) != (m_graph.GetVertex(selSecond.row * 4 + selSecond.col)))) {
		return false;
	}*/
	//判断是否联通
	//此处实例化一个生命周期很短的对象，它会在该函数结束时自动销毁，从而自动销毁栈的数组avPath
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, selFirst, selSecond))
	{
		//确定两个图片相连，销子，并返回相连路径
		gameLogic.Clear(m_graph, selFirst, selSecond);
		
		//返回路径顶点

		//这里有bug
		//bug已解决 line 126
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;

	}
	return false;
}

//判断游戏是否胜利
bool CGameControl::isWin()
{
	return m_GameLogic.isBlank(m_graph);
}

bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	return false;
}

void CGameControl::Reset(void)
{
	m_GameLogic.ResetGraph(m_graph);
}

void CGameControl::OnNMCustomdrawPrbTime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CGameControl::OnEnChangeEditTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CGameControl::OnBnClickedBtnReset()
{
}

void CGameControl::OnBnClickedBtnStart()
{
}




void CGameControl::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
}
