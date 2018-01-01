#include "gameframe.h"

GameFrame::GameFrame(){}

GameFrame::~GameFrame(){}

void GameFrame::doMainLoop(int scrmode){
	//#ifdef DEBUG
	//_CrtSetDbgFlag( );
	//#endif // DEBUG
	SetWindowTextA("RPG K");
	SetWindowIconID(101);
	ChangeWindowMode(scrmode);
	SetGraphMode(800, 450, 32);
	if (DxLib_Init() == -1) return;
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) return;
	setIdouHosei();
	//フォント作成
	largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_EDGE);
	smallfont = CreateFontToHandle(0, 32, 9, DX_FONTTYPE_NORMAL);

	loadFiles();	//各ファイル読み込み
	setGameState(GAMETITLE);	//タイトル画面に設定

	//ウィンドウモード変更と初期化と裏画面設定
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();		//画面消去
		//この中に、コアの処理
		switch(gstate){
		case GAMETITLE:
			drawGameTitle();
			break;
		case GAMEMAIN:
			drawGameMain();
			break;
		case GAMEOVER:
			drawGameOver();
			break;
		case GAMECLEAR:
			drawGameClear();
			break;
		}		
		//ここまでで、コアの処理
		ScreenFlip();
		animcounter = animcounter + 1;
	}
	DxLib_End(); // DXライブラリ終了処理
}

GAMESTATE GameFrame::setGameState(GAMESTATE state){
	if (gstate != state) {
		gstate = state;
		starttime = GetNowCount();
		if(gstate == GAMEMAIN){
			initStage();	//初期化ステージ関数の呼び出し
		}
	}
	return gstate;
}

void GameFrame::drawGameTitle(){
	int col = GetColor(255, 0, 255);
	int w = GetDrawStringWidthToHandle("PUSH Z KEY",12,smallfont);
	DrawStringToHandle(400-w/2,300,"PUSH Z KEY",col,smallfont);

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_A) setGameState(GAMEMAIN);
}

void GameFrame::drawGameMain() {
	int col = GetColor(255, 255, 255);
	DrawStringToHandle(80, 20, "push X to GAMEOVER", col, smallfont);
	DrawStringToHandle(80, 60, "push C to GAMECLEAR", col, smallfont);

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_B) setGameState(GAMEOVER);
	if (key & PAD_INPUT_C) setGameState(GAMECLEAR);
}

void GameFrame::drawGameClear() {
	int col = GetColor(0, 255, 255);
	int w = GetDrawStringWidthToHandle("GAMECLEAR", 9, largefont);
	DrawStringToHandle(400 - w / 2, 160, "GAMECLEAR", col, largefont);

	//w = GetDrawStringWidthToHandle("PUSH Z KEY", 9, smallfont);
	//DrawStringToHandle(320 - w / 2, 300, "PUSH Z KEY", col, smallfont);

	if (GetNowCount() - starttime > 5000) {
		setGameState(GAMETITLE);
	}

	//入力によるシーケンス遷移
	//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (key & PAD_INPUT_A) setGameState(GAMETITLE);
}

void GameFrame::drawGameOver() {
	int col = GetColor(255, 0, 0);
	int w = GetDrawStringWidthToHandle("GAMEOVER", 8, largefont);
	DrawStringToHandle(400 - w / 2, 160, "GAMEOVER", col, largefont);

	//w = GetDrawStringWidthToHandle("PUSH Z KEY", 12, smallfont);
	//DrawStringToHandle(320 - w / 2, 300, "PUSH Z KEY", col, smallfont);

	if (GetNowCount() - starttime > 5000) {
		setGameState(GAMETITLE);
	}

	//入力によるシーケンス遷移
	//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (key & PAD_INPUT_A) setGameState(GAMETITLE);
}

unsigned int GameFrame::getAnimCnt() {
	return animcounter;
}

unsigned int GameFrame::animcounter = 0;

//補正移動量
void GameFrame::setIdouHosei(){
	float frametime = 0;
	unsigned int s = GetNowCount();
	for (int i = 0; i < 30; i++) {
		ScreenFlip();
		unsigned int e = GetNowCount();
		frametime = frametime + e - s;
		s = e;
	}
	frametime = frametime / 30; //30回採取した経過時間の平均をとる
	//
	for (int i = 1; i < 20; i++) {
		idouryou[i] = i / frametime * 16.67;
	}
}

//補正後の移動量を返す
//
float GameFrame::IdouHosei(int idou) {
	if (idou < 0) {
		return(-idouryou[-idou]);
	}
	else {
		return(idouryou[idou]);
	}
}

//idouryouの実体
float GameFrame::idouryou[20];