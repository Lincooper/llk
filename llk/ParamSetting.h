#pragma once
#ifndef PARAMSETTING_H
#define PARAMSETTING_H


#include"global.h"
#include <afxstr.h>
class ParamSetting
{
public:
	static CString BGPath;			//背景图片地址
	static CString ElementPath;		//元素图片地址
	static CString MaskPath;		//掩码图片地址
	static CString ClickSoundPath;	//点击音效地址
	static CString ClearSoundPath;	//消除音效地址
	static CString BgmSoundPath;	//BGM地址

	static int rows;				//地图行
	static int cols;				//地图列
	static int picNum;				//地图包含图片种数
	static int Max_Vertex_Num;		//图片数量

	static bool Bgmon;				//bgm开关
	static int ThemeNo;				//主题编码
}; 
#endif // !PARAMSETTING_H