#ifndef _CHARADATA_H
#define _CHARADATA_H
#include "animdraw.h"

enum ATARIMODE {
	A_GHOST, A_NORMAL, A_HARD, A_MORTAL
	//����Ȃ��A������Ώ��ŁA�ϋv�͂����A�s��
};

struct CharaData {
public:
	float x, y;
	AnimDraw* anim;
	int life;
	int image_w;
	int image_h;
	int bounds_w;
	int bounds_h;
	ATARIMODE amode;
	int yobi[6];
};

#endif
