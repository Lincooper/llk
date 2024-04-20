
// llkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "llk.h"
#include "llkDlg.h"
#include "afxdialogex.h"
#include"CGameDlg.h"
#include"CHelpDlg.h"
#include "CSettingDlg.h"
#include "CGameLevelDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
//	afx_msg void OnInitMenu(CMenu* pMenu);
//	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
//	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
//ON_WM_INITMENU()
//ON_WM_INITMENUPOPUP()
//ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CllkDlg 对话框



CllkDlg::CllkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CllkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CllkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON6, &CllkDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BTN_BASIC, &CllkDlg::OnBnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_HELP, &CllkDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CllkDlg::OnBnClickedBtnLevel)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CllkDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_RANK, &CllkDlg::OnBnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CllkDlg::OnBnClickedBtnRelax)
END_MESSAGE_MAP()


// CllkDlg 消息处理程序

BOOL CllkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBackground();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CllkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CllkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//创建CPaintDC对象
		CPaintDC dc(this);
		//绘制背景图片
		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CllkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CllkDlg::InitBackground()
{
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);
	//llk_main.bmp
	// IDB_BITMAP1
	//创建与视频内存兼容的内存DC
	//获取当前对话框的视频内存
	CClientDC dc(this);

	m_dcMem.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMem.SelectObject(bmpMain);

	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获取窗口大小
	this->GetClientRect(rtClient);	//获取客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	//设置对话窗口位于中央
	CenterWindow();
} 






void CllkDlg::OnBnClickedBtnBasic()
{
	// 隐藏主界面
	this->ShowWindow(SW_HIDE);

	//显示游戏界面，模态对话框
	CGameDlg dlg;
	dlg.SetGameMode(1);
	// 0 休闲
	// 1 基本
	dlg.DoModal();

	//显示主界面
	this->ShowWindow(SW_SHOW);

}


void CllkDlg::OnBnClickedBtnRelax()
{
	// 隐藏主界面
	this->ShowWindow(SW_HIDE);

	//显示游戏界面，模态对话框
	CGameDlg dlg;
	dlg.SetGameMode(0);
	// 0 休闲
	// 1 基本
	dlg.DoModal();

	//显示主界面
	this->ShowWindow(SW_SHOW);
}

void CllkDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	//隐藏主界面
	//this->ShowWindow(SW_HIDE);
	//显示关卡选择，模态展示
	CHelpDlg dlg;
	dlg.DoModal();
	//展示主界面
	this->ShowWindow(SW_SHOW);
}


void CllkDlg::OnBnClickedBtnLevel()
{
	// TODO: 在此添加控件通知处理程序代码
	//隐藏主界面
	this->ShowWindow(SW_HIDE);
	//显示关卡选择，模态展示
	CGameLevelDlg dlg;
	dlg.DoModal();

	//展示主界面
	this->ShowWindow(SW_SHOW);
}


void CllkDlg::OnBnClickedBtnRank()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CllkDlg::OnBnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	//隐藏主界面
	//this->ShowWindow(SW_HIDE);
	//显示关卡选择，模态展示
	CSettingDlg dlg;
	dlg.DoModal();
	//展示主界面
	this->ShowWindow(SW_SHOW);
}







