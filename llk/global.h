//���嶥��ṹ��


#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct {
	int row;//��
	int col;//��
	int info;//ֵΪBLAK��ʾ��ǰ��û��ͼƬ
} Vertex;

#endif // GLOBAL_H
//�궨��

#define GAMEWND_WIDTH	800	//��Ϸ������
#define	GAMEWND_HEIGHT	600	//��Ϸ����߶�
#define MAP_TOP			50	// ��ͼ�����Ϸ�����Ϸ��ļ��
#define MAP_LEFT		20	// ��ͼ�����Ϸ�����󷽵ļ��
#define PIC_WIDTH		40	// ͼƬ���
#define PIC_HEIGHT		40	// ͼƬ�߶�
#define Rows			8	//��ͼ������
#define Cols			8	//��ͼ������
#define PicNum			8	//ͼƬ������
#define MAX_VERTEX_NUM 64   //����ĸ�����Ԫ��������
#define BLANK			-1	//��ͼû��ͼƬ
#define PROGRESS		50	//����ʱ
#define EASY		100	//����ʱ
#define NORMAL		50	//����ʱ
#define HARD		30	//����ʱ