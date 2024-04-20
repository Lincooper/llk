// CGameDlg.cpp: 实现文件
// 用来和用户进行交互,
// 接受用户的鼠标点击事件和按钮的点击事件。

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include <mciapi.h>

#include"global.h"

// CGameDlg 对话框
//CString CGameDlg::BGPath = _T("res/theme/fruit/fruit_bg.bmp");
//CString CGameDlg::ElementPath = _T("res/theme/fruit/fruit_element.bmp");//元素图片路径
//CString CGameDlg::MaskPath = _T("res/theme/fruit/fruit_mask.bmp");//掩码图片路径
//CString CGameDlg::path = _T("res/music/bgm.mp3");
IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)



CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_GameRegionTop.y = MAP_TOP;       //50
	m_GameRegionTop.x = MAP_LEFT;      //20
	m_sizeElem.cx = PIC_WIDTH;         //40
	m_sizeElem.cy = PIC_HEIGHT;        //40

	m_GameRegion.top = MAP_TOP;
	m_GameRegion.left = MAP_LEFT;
	m_GameRegion.right = MAP_LEFT + PIC_WIDTH * Cols;
	m_GameRegion.bottom = MAP_TOP + PIC_HEIGHT * Rows;

	playing = false;
	firstSelect = false;
	GameMode = 0;
}

CGameDlg::~CGameDlg()
{
	OnClose();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRB_TIME, GameProgress);//将滚动条和控件绑在一起
}

void CGameDlg::InitBackground()
{
	//加载背景，留着后面更新地图使用
	if (ParamSetting::ThemeNo == 0) {
		//水果乐园主题
		ParamSetting::BGPath =			_T("res/theme/fruit/fruit_bg.bmp");
		ParamSetting::ElementPath =		_T("res/theme/fruit/fruit_element.bmp");
		ParamSetting::MaskPath =		_T("res/theme/fruit/fruit_mask.bmp");
		ParamSetting::ClickSoundPath =	_T("res/theme/fruit/music/fruit_click.wav");
		ParamSetting::ClearSoundPath =	_T("res/theme/fruit/music/fruit_clear.wav");
		ParamSetting::BgmSoundPath =	_T("res/theme/fruit/music/fruit_bgm.mp3");
	}
	else if (ParamSetting::ThemeNo == 1) {
		//坤坤主题
		ParamSetting::BGPath =			_T("res/theme/cxk/cxk_bg.bmp");
		ParamSetting::ElementPath =		_T("res/theme/cxk/cxk_element.bmp");
		ParamSetting::MaskPath =		_T("res/theme/cxk/cxk_mask.bmp");
		ParamSetting::ClickSoundPath =	_T("res/theme/cxk/music/cxk_click.wav");
		ParamSetting::ClearSoundPath =	_T("res/theme/cxk/music/cxk_clear.wav");
		ParamSetting::BgmSoundPath =	_T("res/theme/cxk/music/cxk_bgm.mp3");
	}
	else if(ParamSetting::ThemeNo == 2){
		//怪物猎人主题
		ParamSetting::BGPath =			_T("res/theme/mh/mh_bg.bmp");
		ParamSetting::ElementPath =		_T("res/theme/mh/mh_element.bmp");
		ParamSetting::MaskPath =		_T("res/theme/mh/mh_mask.bmp");
		ParamSetting::ClickSoundPath =	_T("res/theme/mh/music/mh_click.wav");
		ParamSetting::ClearSoundPath =	_T("res/theme/mh/music/mh_clear.wav");
		ParamSetting::BgmSoundPath =	_T("res/theme/mh/music/mh_bgm.mp3");
	}
	HANDLE Backbmp = ::LoadImageW(NULL, ParamSetting::BGPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(Backbmp);

	//加载内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//处理窗口
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

void CGameDlg::SetGameMode(int mode)
{
	this->GameMode = mode;
}

void CGameDlg::InitMode(int mode)
{
	CProgressCtrl* pProgressCtrl = (CProgressCtrl*)GetDlgItem(IDC_PRB_TIME);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TIME);

	if (mode == 1) {
		this->SetWindowTextW(_T("欢乐连连看--基本模式"));
		pEdit->EnableWindow(FALSE);
	}
	else if (mode == 0) {
		this->SetWindowTextW(_T("欢乐连连看--休闲模式"));
		pProgressCtrl->ShowWindow(SW_HIDE);
		pEdit->EnableWindow(FALSE);
	}
	else{
		this->SetWindowTextW(_T("欢乐连连看--关卡模式"));
	}
		
}


void CGameDlg::SetButton(bool start, bool stop, bool prompt, bool reset)
{
	//各个按钮
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(start);
	this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(stop);
	this->GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(prompt);
	this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(reset);
}

//初始化连连看元素
void CGameDlg::InitElement(CString ElementPath, CString MaskPath)
{
	
	CClientDC dc(this); 
	//加载元素图片
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcEle.CreateCompatibleDC(&dc);
	m_dcEle.SelectObject(hBmp);
	//加载掩码图片
	HANDLE hMask = ::LoadImageW(NULL, MaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);


	//加载掩盖图片
	HANDLE hCache = ::LoadImage(NULL, _T("res//pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcCache.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcCache.SelectObject(hCache);
}

void CGameDlg::UpdateMap()
{
	//读取地图信息，并在界面上显示
	int nTop = MAP_TOP;
	int nLeft = MAP_LEFT;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_WIDTH;
	/*int row = ParamSetting::rows;
	int col = ParamSetting::cols;*/

	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Cols; j++) {
			int nElemNal = m_GameC.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH ,&m_dcMask,0, nElemNal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH ,&m_dcEle, 0, nElemNal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::SetGameProgress(int range)
{
	//设置游戏倒计时 range为设置的时间 PROGRESS为100
	GameProgress.SetRange(0, range);
	GameProgress.SetStep(-1);
	GameProgress.SetPos(range);
	TimeCount = range;
	this->SetTimer(1, 1000, NULL);
}

void CGameDlg::TurnonBGMusic(CString path)
{
	if (mciSendString(_T("open " + path + " alias BGM"),NULL, 0, NULL) != 0) {
		//ASSERT(0);
	}
		
	mciSendString(_T("play BGM repeat"), NULL, 0, NULL);
}

void CGameDlg::TurnoffBGMusic()
{
	mciSendString(_T("stop BGM"), NULL, 0, NULL);
	mciSendString(_T("close BGM"), NULL, 0, NULL);
}

void CGameDlg::OnClose()
{
	TurnoffBGMusic();
	CDialogEx::OnClose();
}





BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
//	ON_WM_ACTIVATEAPP()
//	ON_WM_ACTIVATE()
ON_WM_PAINT()
//ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnBnClickedBtnPrompt)
ON_BN_CLICKED(IDC_BTN_STOP, &CGameDlg::OnBnClickedBtnStop)
ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
ON_WM_LBUTTONUP()
ON_WM_TIMER()
END_MESSAGE_MAP()



// CGameDlg 消息处理程序
//此为虚函数
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//让弹出的窗口作为应用程序窗口显示
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);

	//设置背景
	InitBackground();

	//设置模式
	InitMode(this->GameMode);

	//设置游戏窗口按钮的初始状态
	//开始游戏为可按 其他不可按
	SetButton(TRUE, FALSE, FALSE, FALSE);


	//初始化加载水果元素和掩码
	InitElement(ParamSetting::ElementPath, ParamSetting::MaskPath);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	// 不为绘图消息调用 
	CDialogEx::OnPaint();
}




void CGameDlg::OnBnClickedBtnPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得当前对话框的视频内容
	CClientDC dc(this);
	//如果游戏没有暂停
	if (pause == false)
	{
		playing = false;
		//hu绘制背景到内存DC中
		//m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		m_dcMem.BitBlt(0, 0, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		UpdateMap();
		//GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(0);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(0);
		InvalidateRect(m_GameRegion, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BTN_STOP)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停
	if (pause == true)
	{
		playing = true;
		UpdateMap();
		//GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(1);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(1);
		InvalidateRect(m_GameRegion, FALSE);    //局部矩形更新

		this->GetDlgItem(IDC_BTN_STOP)->SetWindowTextW(_T("暂停游戏"));
	}

	pause = !pause;
}


void CGameDlg::OnBnClickedBtnStart()
{
	//暂停时不响应
	if (pause == true) return;
	// 初始化地图，地图用一个二维数组保存
	/*bool status = m_GameC.StartGame(ParamSetting::rows, ParamSetting::cols, ParamSetting::picNum);*/
	bool status = m_GameC.StartGame(Rows, Cols, PicNum); 
	if (status) {
		//设置状态
		playing = true;
		firstSelect = true;

		//设置按钮
		SetButton(FALSE, TRUE, TRUE, TRUE);
		UpdateMap();//展示地图信息
		
		if (ParamSetting::Bgmon) {
			TurnonBGMusic(ParamSetting::BgmSoundPath);
		}
		
		//不是休闲模式，则设置滚动条和定时器
		switch (this->GameMode)
		{
			case 1:
			case 2:SetGameProgress(EASY);
				break;
			case 3:SetGameProgress(NORMAL);
				break;
			case 4:SetGameProgress(HARD);
				break;
			default:
				break;
		}
		
	}
	else {
		AfxMessageBox(L"行列和图片个数不匹配，无法绘制地图！", MB_OKCANCEL);
	}
	
	InvalidateRect(FALSE);
}


void CGameDlg::OnBnClickedBtnReset()
{
	//调用CGameControl：：ResetGraph();
	m_GameC.Reset();

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	
	//更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();

	//通知界面重绘
	InvalidateRect(m_GameRegion, FALSE);    //局部矩形更新
}




void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//如果非游戏状态 不可点击
	if (!playing)
		return;

	//判断点击是否有效
	if (point.y < m_GameRegion.top || point.y > m_GameRegion.bottom || point.x < m_GameRegion.left || point.x > m_GameRegion.right)
		return;

	//对坐标进行整除 获得选中的元素的行、列值
	int nRow = (point.y - m_GameRegionTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_GameRegionTop.x) / m_sizeElem.cx;
	if (nRow > Rows- 1 || nCol > Cols - 1)
		return;

	//若在地图内且无可选中的元素 点击无效
	if (m_GameC.GetElement(nRow, nCol) == BLANK)
		return;

	//如果是点击为第一次点击 则画边框，并进行设置
	if (firstSelect) {
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
		PlaySound(ParamSetting::ClickSoundPath, NULL, SND_FILENAME | SND_ASYNC);
	}
	else {
	//如果是点击为第一次点击 
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecondPoint(nRow, nCol);
		//同时判断两个点是否相连
		stack<Vertex> verList;

		/*int num = ParamSetting::rows * ParamSetting::cols;*/
		//Vertex* avPath = new Vertex[num];
		Vertex avPath[MAX_VERTEX_NUM];	
		int nVexnum = 0;
		
		bool bSuc = m_GameC.Link(avPath, nVexnum);
		
		if (bSuc) {
			//如果相连，则画连线
			//DrawTipLine(verList);
			DrawTipLine1(avPath, nVexnum);
			//重新加载地图背景，并更新最新地图
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
			UpdateMap();
			PlaySound(ParamSetting::ClearSoundPath, NULL, SND_FILENAME | SND_ASYNC);
			//CGameLogic::m_anPath[CGameLogic::m_nVexNum] = NULL;
		}
		Sleep(200);
		InvalidateRect(FALSE);
		if (bSuc && m_GameC.isWin()) {
			MessageBox(TEXT("恭喜你！获胜！"));
			//设置按钮
			SetButton(TRUE, FALSE, FALSE, FALSE);
			playing = false;
		}
	}
	//第一次和第二次点击切换标志
	firstSelect = !firstSelect;
}



//画框函数
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_GameRegionTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_GameRegionTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


//画线函数
void CGameDlg::DrawTipLine(stack<Vertex>verList)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);
	Vertex vTop;
	CPoint cp;
	if (!verList.empty())
	{
		vTop = verList.top();
		cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
		cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
		dc.MoveTo(cp);
		verList.pop();
		while (!verList.empty())
		{
			vTop = verList.top();
			cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
			cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
			dc.LineTo(cp);
			verList.pop();
		}
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::DrawTipLine1(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_GameRegionTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_GameRegionTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_GameRegionTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_GameRegionTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (playing) {
		//设置Edit文本值
		//定时器和滚动条随时间递减
		CString str; 
		str.Format(_T("%d"), TimeCount - 1);
		SetDlgItemText(IDC_EDIT_TIME, str);
		UpdateData(false);
		TimeCount--;
		GameProgress.StepIt();

		if (TimeCount == 0) {
			//关掉定时器
			KillTimer(1);
			m_GameC.ClearMap();//清空地图
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
			UpdateMap();
			
			InvalidateRect(FALSE);
			//OnClose();
			MessageBox(TEXT("时间到!游戏失败!"));
			SetButton(TRUE, FALSE, FALSE, FALSE);
			playing = false;	
			
		}
				
				
	}
	

	CDialogEx::OnTimer(nIDEvent);
}
