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
	static unsigned int animcounter;		//アニメーション用カウンター
protected:
	virtual void drawGameTitle();	//タイトル画面
	virtual void drawGameMain();	//ゲーム本体
	virtual void drawGameOver();	//ゲームオーバー画面
	virtual void drawGameClear();	//ゲームクリア画面
	GAMESTATE setGameState(GAMESTATE state);
	int largefont, smallfont;
public:
	GameFrame();
	virtual ~GameFrame();
	void doMainLoop(int);
	static unsigned int getAnimCnt();		//animcounterの取得
};

#endif
