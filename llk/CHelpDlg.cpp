// CHelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CHelpDlg.h"




// CHelpDlg 对话框

CString CHelpDlg::HelpPath = _T("res/Setting.bmp");

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	SetIcon(m_hIcon, TRUE);    //
	SetIcon(m_hIcon, FALSE);   //

	InitHelp();

	
	


	

	////设置滚动条范围
	//CBitmap bmpHelp;
	//bmpHelp.Attach(hBmpHelp);
	//BITMAP bmpInfo;
	//bmpHelp.GetBitmap(&bmpInfo);

	////设置滚动条的范围
	//((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR_HELP))->SetScrollRange(0, bmpInfo.bmHeight);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CHelpDlg::InitHelp()
{
	//加载背景，留着后面更新地图使用

	HANDLE Backbmp = ::LoadImageW(NULL, HelpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(Backbmp);

	//加载内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcHelp, 0, 0, SRCCOPY);
	////绘制白色背景
	//m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);
	//处理窗口
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获取窗口大小
	this->GetClientRect(rtClient);	//获取客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, 500 + nSpanWidth, 372 + nSpanHeight);

	//设置对话窗口位于中央	
	CenterWindow();


	////绘制帮助信息显示区域
	//this->GetDlgItem(IDD_HELP_DIALOG)->GetWindowRect(&m_rtHelp);
	//this->ScreenToClient(&m_rtHelp);
	////绘制帮助信
	//UpdateHelp(0);
}

void CHelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	 dc.BitBlt(0, 0, 500, 372, &m_dcMem, 0, 0, SRCCOPY);
	//CRect  rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为绿色背景

	////hu绘制背景到内存DC中
	//m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);

	////绘制背景图片
	//dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}

void CHelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CHelpDlg::UpdateHelp(int nPos)
{
	//将重绘区，绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序
