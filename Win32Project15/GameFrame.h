#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

#include "Title.h"
#include "Sound.h"
#include "DxLib.h"
#include "TextParam.h"
#include "GameMain.h"

// 共有効果音
typedef enum _ECommonSE
{
	ECommonSE_Alert,		// 警告
	ECommonSE_Cancel,		// キャンセル
	ECommonSE_Counter,		// カウント
	ECommonSE_Cursor,		// カーソル
	ECommonSE_Enter,		// 決定

	ECommonSE_Num,			// 共有効果音の数
} ECommonSE;

class GameFrame {

private:

	//ゲームモードの状態
	enum GameMode {

		GAME_TITLE,
		GAME_MAIN,
		GAME_EXIT,

		GAME_MODE_NUM,
	} gameMode;


	//フォントハンドルの種類
	enum font {

		EFontHandle_Small,
		EFontHandle_Midium,
		EFontHandle_Big,

		EFontHandle_Num,
	};



	Title*		mTitle;
	GameMain*	mGameMain;

	struct SGameFrameInfo{

		//低処理負荷モード変数
		bool LowSpecMode;

		//フォントハンドル変数
		int	FontHandle[EFontHandle_Num];

		// 共有効果音のハンドル
		int	CommonSEHandle[ECommonSE_Num];

		//状態推移時間など
		double		stepTime;
		LONGLONG	prevTime;
		int			stepNum;

		// フレームレート計測用の変数の初期化
		LONGLONG backDispFrameTime;
		int frameCounter;
		int dispFrameCount;

	} s_GameFrameInfo;




public:

	typedef struct _STask_GameFrameData{

		Task::STaskInfo			Info;

	} STask_GameFrameData;

	STask_GameFrameData		TGData;

	TextParam*	mTextParam;
	Sound*		mSound;

	GameFrame();

	~GameFrame();

	//メインの処理
	void	Main();

	//初期化処理
	void	Initialize();

	//メインループ
	void	MainLoop( Task::STaskInfo		TInfo );

	//後始末処理
	void	Terminate();

};

#endif
