#include <math.h>
#include "DxLib.h"
#include "gameframe.h"
#include "animdraw.h"

#define PI 3.141592654f

class CurGame :public GameFrame {
	void drawGameTitle();
	AnimDraw okojyo;
	void loadFiles() throw(int);
	void drawGameMain();
};

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hp, LPSTR lpC, int nC){
	CurGame* cg = new CurGame();

	cg->doMainLoop(TRUE);

	delete cg;
}

void CurGame::drawGameTitle(){
	SoundBox::playbgm(0);
	int col = GetColor(0, 255, 128);
	DrawBox(0,0,800,240,col,TRUE);

	GameFrame::drawGameTitle();
}

void CurGame::loadFiles() throw(int) {
	int shandle = LoadSoundMem("be00101.wav"); //音楽データファイル
	if (shandle == -1) throw(-2);
	SoundBox::set(shandle);
	shandle = LoadSoundMem("cr00101.wav");
	if (shandle == -1) throw(-2);
	SoundBox::set(shandle);
	shandle = LoadSoundMem("ho00101.wav");
	if (shandle == -1) throw(-2);
	SoundBox::set(shandle);

	int ghandle[8];
	if (LoadDivGraph("imgres.png", 8, 4, 2, 79, 79, ghandle) == -1)
throw(-1);
	okojyo.setImage(0, ghandle[0]);
	okojyo.setImage(0, ghandle[1]);
	okojyo.setImage(0, ghandle[2]);
	okojyo.setImage(0, ghandle[3]);
	okojyo.setGap(0, 6);
	okojyo.setImage(1, ghandle[4]);
	okojyo.setImage(1, ghandle[4]);
	okojyo.setImage(1, ghandle[5]);
	okojyo.setImage(1, ghandle[6]);
	okojyo.setImage(1, ghandle[7]);
	okojyo.setImage(1, ghandle[7]);
	okojyo.setImage(1, ghandle[7]);
	okojyo.setImage(1, ghandle[7]);
	okojyo.setGap(1, 4);
}

void CurGame::drawGameMain() {
	SoundBox::playbgm(1);
	GameFrame::drawGameMain();//基底クラスの同関数を呼び出し
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		for (int i = 0; i < 5; i++) {
			if (key & PAD_INPUT_A) {
				SoundBox::play(2);
				okojyo.draw(1,140+i*70,300);
			}
			else {
				okojyo.draw(0,140+i*70,300);
			}
		}
}