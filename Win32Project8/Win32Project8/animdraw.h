#ifndef _ANIMDRAW_H
#define _ANIMDRAW_H

#include <vector>
#include "DxLib.h"
#include "gameframe.h"
using namespace std;

class AnimDraw {
	struct animpat {	//構造体
		vector<int> ghlist;
		int anigap;
		animpat() { anigap = 1; }	//コンストラクタ
	};
	vector<animpat> aplist;
public:
	AnimDraw() {
		aplist.push_back( animpat() );		//一つ目のanimpat
	}

	int setImage( int apid, int ghandle);//グラフィックハンドルをセットする
	int setGap(int apid, int gap);

	void draw(int apid, int x, int y);
	void draw(int apid, int x, int y, float rad);//アニメーション回転表示
};

class SoundBox {
	static vector<int> sounds;
	static int bgm;
public:
	static int set(int shandle);
	static void play(int snum);
	static void stop(int snum);
	static void playbgm(int snum);
};

#endif