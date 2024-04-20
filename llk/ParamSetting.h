#pragma once
#ifndef PARAMSETTING_H
#define PARAMSETTING_H


#include"global.h"
#include <afxstr.h>
class ParamSetting
{
public:
	static CString BGPath;			//����ͼƬ��ַ
	static CString ElementPath;		//Ԫ��ͼƬ��ַ
	static CString MaskPath;		//����ͼƬ��ַ
	static CString ClickSoundPath;	//�����Ч��ַ
	static CString ClearSoundPath;	//������Ч��ַ
	static CString BgmSoundPath;	//BGM��ַ

	static int rows;				//��ͼ��
	static int cols;				//��ͼ��
	static int picNum;				//��ͼ����ͼƬ����
	static int Max_Vertex_Num;		//ͼƬ����

	static bool Bgmon;				//bgm����
	static int ThemeNo;				//�������
}; 
#endif // !PARAMSETTING_H