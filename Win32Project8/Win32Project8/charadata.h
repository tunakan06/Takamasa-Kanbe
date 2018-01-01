#ifndef _CHARADATA_H
#define _CHARADATA_H
#include "animdraw.h"

enum ATARIMODE {
	A_GHOST, A_NORMAL, A_HARD, A_MORTAL
	//判定なし、当たれば消滅、耐久力を持つ、不死
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
