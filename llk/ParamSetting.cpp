#include "pch.h"
#include "ParamSetting.h"
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

CString ParamSetting::BGPath = _T("res/theme/mh/mh_bg.bmp");
CString ParamSetting::ElementPath =	_T("res/theme/mh/mh_element.bmp");
CString ParamSetting::MaskPath = _T("res/theme/mh/mh_mask.bmp");
CString ParamSetting::ClickSoundPath = _T("res/theme/mh/music/mh_click.wav");
CString ParamSetting::ClearSoundPath = _T("res/theme/mh/music/mh_clear.wav");
CString ParamSetting::BgmSoundPath = _T("res/theme/mh/music/mh_bgm.mp3");

int ParamSetting::rows = 6;
int ParamSetting::cols = 6;
int ParamSetting::picNum = 6;
int ParamSetting::Max_Vertex_Num = 36;

bool ParamSetting::Bgmon =false;
int ParamSetting::ThemeNo = 0;