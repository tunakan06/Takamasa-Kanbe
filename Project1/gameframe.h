#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

#include "DxLib.h"

enum GAMESTATE {
	GAMETITLE = 1,
	GAMEMAIN,
	GAMEOVER,
	GAMECLEAR
};

class GameFrame {
	virtual void loadFiles(){}
	virtual void initStage(){}
	GAMESTATE gstate;
	int starttime;
	static unsigned int animcounter;		//�A�j���[�V�����p�J�E���^�[
protected:
	virtual void drawGameTitle();	//�^�C�g�����
	virtual void drawGameMain();	//�Q�[���{��
	virtual void drawGameOver();	//�Q�[���I�[�o�[���
	virtual void drawGameClear();	//�Q�[���N���A���
	GAMESTATE setGameState(GAMESTATE state);
	int largefont, smallfont;
public:
	GameFrame();
	virtual ~GameFrame();
	void doMainLoop(int);
	static unsigned int getAnimCnt();		//animcounter�̎擾
};

#endif
