#ifndef _TITLE_H
#define _TITLE_H

#include "DxLib.h"
#include "Sound.h"

static const char *g_TitleMenuTable[] =
{
	"GAME START",
	"CONTINUE GAME",
	"EXIT" };

class Title{

public:

	//タイトル生成
	Title();

	//デストラクタ
	~Title();

	//選択モードの遷移状態
	enum TitleState {

		FADEIN_WAIT,
		FADEIN,
		MENUIN_WAIT,
		MENUIN,
		SELECT,

		TITLE_STATE_NUM,

	};

	//決定した選択モード
	enum SelectMode {

		SELECT_NEW,
		SELECT_CONTINUE,
		SELECT_EXIT,

		SELECT_MODE_NONE,

		SELECT_MODE_NUM,

	};

	//タイトルの処理の状態
	TitleState	titleState;

	//決定した選択モード
	SelectMode	selectMode;

	//タイトル画面出力
	int Draw( float StepTime );

	//タイトル画面後始末
	void Terminate();

private:

	Sound* tSound;

	//タイトル画面で使用するフォントの作成
	int menuFont;

	//タイトル画面格納変数
	int titleBackGraphic;

	//ロゴ画面格納変数
	int logoGraphic;

	//サウンド格納変数
	int titlesound;

	//メニュー項目のY座標
	int DrawY;

	//描画色
	int DrawColor;

	//選択モードとそれ以外のの表示色
	int SelectColor;
	int NormalColor;

	//タイトルとメニュー項目の不透明度
	int titleOpacity;
	int menuOpacity;

	//汎用カウンタ
	float counter;

	//選択項目の明滅用カウンタ
	float menuBrinkCounter;

	//モードセレクト処理
	void selectModeSequence( SelectMode smode );


};

#endif
