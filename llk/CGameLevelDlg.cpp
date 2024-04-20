// CGameLevelDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CGameLevelDlg.h"
#include "CGameDlg.h"


// CGameLevelDlg 对话框
CString CGameLevelDlg::LevelPath = _T("res/level.bmp");
IMPLEMENT_DYNAMIC(CGameLevelDlg, CDialogEx)

CGameLevelDlg::CGameLevelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEVEL_DIALOG, pParent)
{

}

CGameLevelDlg::~CGameLevelDlg()
{
	

}

void CGameLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CGameLevelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);    
	SetIcon(m_hIcon, FALSE);   
	//添加背景
	InitBackground();
	return true;
}

void CGameLevelDlg::SetLevel(int level)
{
	//隐藏主界面
	this->ShowWindow(SW_HIDE);
	//显示关卡选择，模态展示
	CGameDlg dlg;
	dlg.SetGameMode(level);
	dlg.DoModal();

	//展示主界面
	this->ShowWindow(SW_SHOW);
}

void CGameLevelDlg::InitBackground()
{

	HANDLE Backbmp = ::LoadImageW(NULL, LevelPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcLevel.CreateCompatibleDC(&dc);
	m_dcLevel.SelectObject(Backbmp);

	//加载内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 508);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 1000, 1000, &m_dcLevel, 0, 0, SRCCOPY);
	//调整窗口大小
	CRect rtWin; 
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 508 + nSpanHeight);
	CenterWindow();
}




BEGIN_MESSAGE_MAP(CGameLevelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EASY_BUTTON, &CGameLevelDlg::OnBnClickedEasyButton)
	ON_BN_CLICKED(IDC_NORMAL_BUTTON, &CGameLevelDlg::OnBnClickedNormalButton)
	ON_BN_CLICKED(IDC_HARD_BUTTON, &CGameLevelDlg::OnBnClickedHardButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameLevelDlg 消息处理程序



void CGameLevelDlg::OnBnClickedEasyButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(2);//简单
}


void CGameLevelDlg::OnBnClickedNormalButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(3);//普通
}


void CGameLevelDlg::OnBnClickedHardButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SetLevel(4);//困难
}



void CGameLevelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 508, &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}
