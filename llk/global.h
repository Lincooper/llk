//定义顶点结构体


#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct {
	int row;//行
	int col;//列
	int info;//值为BLAK表示当前点没有图片
} Vertex;

#endif // GLOBAL_H
//宏定义

#define GAMEWND_WIDTH	800	//游戏界面宽度
#define	GAMEWND_HEIGHT	600	//游戏界面高度
#define MAP_TOP			50	// 地图距高游戏界面上方的间距
#define MAP_LEFT		20	// 地图距高游戏界面左方的间距
#define PIC_WIDTH		40	// 图片宽度
#define PIC_HEIGHT		40	// 图片高度
#define Rows			8	//地图的行数
#define Cols			8	//地图的行数
#define PicNum			8	//图片的种数
#define MAX_VERTEX_NUM 64   //顶点的个数（元素数量）
#define BLANK			-1	//地图没有图片
#define PROGRESS		50	//倒计时
#define EASY		100	//倒计时
#define NORMAL		50	//倒计时
#define HARD		30	//倒计时