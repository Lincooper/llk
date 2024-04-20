// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"
#include "ParamSetting.h"



// CSettingDlg 对话框
CString CSettingDlg::SetPath = _T("res/Setting.bmp");
IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CSettingDlg::InitSetting()
{
	//加载背景，留着后面更新地图使用

	HANDLE Backbmp = ::LoadImageW(NULL, SetPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcSet.CreateCompatibleDC(&dc);
	m_dcSet.SelectObject(Backbmp);

	//加载内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcSet, 0, 0, SRCCOPY);
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
}

BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);    //
	SetIcon(m_hIcon, FALSE);   //
	//添加背景
	InitSetting();
	//增加下拉框数据的初始化
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_THEME);
	pCombo->InsertString(0, _T("水果乐园主题"));
	pCombo->InsertString(1, _T("只因你太美主题"));
	pCombo->InsertString(2, _T("怪物猎人主题"));
	pCombo->SetCurSel(ParamSetting::ThemeNo);
	//行列图片数据初始化
	CEdit* editRow = (CEdit*)GetDlgItem(IDC_EDIT_ROW);
	CEdit* editCol = (CEdit*)GetDlgItem(IDC_EDIT_COL);
	//CEdit* editPic = (CEdit*)GetDlgItem(IDC_EDIT_PIC);
	CString rows, cols, pics; 
	rows.Format(_T("%d"), ParamSetting::rows); 
	cols.Format(_T("%d"), ParamSetting::cols); 
	pics.Format(_T("%d"), ParamSetting::picNum);
	editRow->SetWindowTextW(rows);
	editCol->SetWindowTextW(cols);
	//editPic->SetWindowTextW(pics);
	//背景音乐按钮的初始化
	CButton* radioOpen = (CButton*)GetDlgItem(IDC_RADIO_OPEN);
	CButton* radioClose = (CButton*)GetDlgItem(IDC_RADIO_CLOSE);
	if (ParamSetting::Bgmon) {
		radioOpen->SetCheck(BST_CHECKED);
	}
	else {
		radioClose->SetCheck(BST_CHECKED);
	}
	return TRUE;
}

void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	 dc.BitBlt(0, 0, 500, 372, &m_dcMem, 0, 0, SRCCOPY);
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为绿色背景

	////hu绘制背景到内存DC中
	//m_dcMem.BitBlt(0, 0, m_rtSet.Width(), m_rtSet.Height(), &m_dcSet, 0, 0, SRCCOPY);

	////绘制背景图片
	//dc.BitBlt(0, 0, m_rtSet.Width(), m_rtSet.Height(), &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}





void CSettingDlg::SetTheme(int theme)
{
	ParamSetting::ThemeNo = theme;
}

void CSettingDlg::SetMap(int row, int col, int picNum)
{
	ParamSetting::rows = row;
	ParamSetting::cols = col;
}

void CSettingDlg::SetBGM(bool musicOn)
{
	ParamSetting::Bgmon = musicOn;
}

bool CSettingDlg::IsNum(CString s)
{
	return false;
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_RADIO_CLOSE, &CSettingDlg::OnBnClickedRadioClose)
ON_BN_CLICKED(IDC_RADIO_OPEN, &CSettingDlg::OnBnClickedRadioOpen)
ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
ON_CBN_SELCHANGE(IDC_COMBO_THEME, &CSettingDlg::OnCbnSelchangeComboTheme)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序
void CSettingDlg::OnBnClickedRadioOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	musicOn = true;
}


void CSettingDlg::OnBnClickedRadioClose()
{
	// TODO: 在此添加控件通知处理程序代码
	musicOn = false;
}




void CSettingDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//提取主题信息
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_THEME);
	int nIndex = pCombo->GetCurSel();
	SetTheme(nIndex);
//提取地图信息
	CEdit* editRow = (CEdit*)GetDlgItem(IDC_EDIT_ROW);
	CEdit* editCol = (CEdit*)GetDlgItem(IDC_EDIT_COL);
	//提取背景音乐信息
	SetBGM(musicOn);
	CDialogEx::OnOK();
	//CEdit* editPic = (CEdit*)GetDlgItem(IDC_EDIT_PIC);
	/*CString row, col, pic;
	int rows, cols, pics;*/
	//editRow->GetWindowText(row);
	//if (!IsNum(row)) {
	//	;
	//}
	//rows = _ttoi(row);
	//if (rows < 1 || rows>10) {
	//	;
	//}
	//editCol->GetWindowText(col);
	//if (!IsNum(col))cols = _ttoi(col);
	//if (cols < 1 || cols>10) {
	//	//editPic->GetWindowText(pic);
	//	;
	//}
	//if (!IsNum(pic)) {
	//	pics = _ttoi(pic);
	//}
	//if (pics < 1 || pics>16) {
	//	;
	//}
	//if ((rows * cols) % (pics * 2)) {
	//	SetMap(rows, cols, pics);
	//}
	
}




void CSettingDlg::OnCbnSelchangeComboTheme()
{
	// TODO: 在此添加控件通知处理程序代码
}
