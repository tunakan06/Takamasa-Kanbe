#ifndef _ANIMDRAW_H
#define _ANIMDRAW_H

#include <vector>
#include "DxLib.h"
#include "gameframe.h"
using namespace std;

class AnimDraw {
	struct animpat {	//�\����
		vector<int> ghlist;
		int anigap;
		animpat() { anigap = 1; }	//�R���X�g���N�^
	};
	vector<animpat> aplist;
public:
	AnimDraw() {
		aplist.push_back( animpat() );		//��ڂ�animpat
	}

	int setImage( int apid, int ghandle);//�O���t�B�b�N�n���h�����Z�b�g����
	int setGap(int apid, int gap);

	void draw(int apid, int x, int y);
	void draw(int apid, int x, int y, float rad);//�A�j���[�V������]�\��
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