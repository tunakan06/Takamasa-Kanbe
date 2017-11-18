#include "GameFrame.h"

#define		MAX_DELTA_TIME		1.0/120.0f
#define		MAX_FRAME_NUM		8
#define		GAME_SCREEN_WIDTH	1200
#define		GAME_SCREEN_HEIGHT	720

// 共有効果音のファイル名
static const char *g_CommonSEFileName[ECommonSE_Num] =
{
	"system_alert.wav",
	"system_cancel.wav",
	"system_counter.wav",
	"system_cursor.wav",
	"system_enter.wav",
};

GameFrame::GameFrame() {


}

GameFrame::~GameFrame() {



}

//メインの処理
void	GameFrame::Main( ){

	Task::STaskInfo TInfo = TGData.Info;

	//初期化処理
	Initialize();

	//メインループ
	MainLoop( TInfo );

	//後始末処理
	Terminate();

}

//初期化処理
void	GameFrame::Initialize() {

	int		i;
	char	FilePath[ MAX_PATH ];

	//ウィンドウモードで起動するか確認
	if ( MessageBox( NULL, "ウィンドウモードで起動しますか？", "画面モード確認", MB_YESNO ) == IDYES ) {
		
		ChangeWindowMode(TRUE);

	}

	//低負荷処理モードで起動するか確認
	if (MessageBox(NULL, "低負荷処理モードで起動しますか？", "処理負荷モード確認", MB_YESNO) == IDYES) {

		s_GameFrameInfo.LowSpecMode = true;
	
	}

	//ゲーム画面解像度設定
	SetGraphMode( GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);

	//ウィンドウのタイトルを設定
	SetMainWindowText("Sword Bout");

	//低負荷処理モードかどうかでXAudioを使用するかどうかの設定変更
	SetEnableXAudioFlag( s_GameFrameInfo.LowSpecMode ? FALSE : TRUE );

	//3Dサウンドの1メートル当たりの値をセット
	Set3DSoundOneMetre( 100.0f );

	DrawStringToHandle(1000, 650, "Now Loading...", GetColor(100, 100, 100), s_GameFrameInfo.FontHandle[EFontHandle_Small]);

	//DXライブラリ初期化処理
	DxLib_Init();

	//フォントハンドルの作成
	s_GameFrameInfo.FontHandle[EFontHandle_Small] = CreateFontToHandle(NULL, 24, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	s_GameFrameInfo.FontHandle[EFontHandle_Midium] = CreateFontToHandle(NULL, 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	s_GameFrameInfo.FontHandle[EFontHandle_Big] = CreateFontToHandle(NULL, 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);

	//共有効果音の読み込み
	for (i = 0; i < ECommonSE_Num ; i++ ) {
		sprintf_s( FilePath, "Data\\Sound\\SE\\Common\\%s", g_CommonSEFileName[ i ] );
		s_GameFrameInfo.CommonSEHandle[i] = LoadSoundMem( FilePath );

	}

	DrawStringToHandle(1000,650,"Now Loading...", GetColor(100,100,100), s_GameFrameInfo.FontHandle[EFontHandle_Small]);

	//タイトル生成
	mTitle = new Title();

	//サウンド生成
	mSound = new Sound();

	//テキストパラメータ生成
	//mTextParam = new TextParam();

	//先ずはタイトル画面を出力
	gameMode = GAME_TITLE;

	//ゲームメイン生成
	mGameMain = new GameMain();

	s_GameFrameInfo.backDispFrameTime = GetNowHiPerformanceCount();
	s_GameFrameInfo.frameCounter = 0;
	s_GameFrameInfo.dispFrameCount = 0;

}

//メインループ
void	GameFrame::MainLoop( Task::STaskInfo		TInfo ) {
	
	LONGLONG			NowTime;

	//描画先は裏画面
	SetDrawScreen( DX_SCREEN_BACK );

	//最初のフレームの状態推移時間などをセット
	s_GameFrameInfo.stepTime = MAX_DELTA_TIME;
	s_GameFrameInfo.prevTime = GetNowHiPerformanceCount();
	s_GameFrameInfo.stepNum = 1;

	//タイトルミュージック再生
	mSound->Output(0);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {//画面更新 & メッセージ処理 & 画面消去

		switch (gameMode) {
		case GAME_TITLE:
			//タイトル画面出力
			if (mTitle->Draw(s_GameFrameInfo.stepTime ) == Title::SELECT_NEW) {//zキーでゲームメインへ

				//タイトルサウンド停止
				mSound->stopSound( 0 );

				//サウンド出力
				mSound->Output(1);

				//タイトルの後始末
				mTitle->Terminate();

				//ゲームのメインへ
				gameMode = GAME_MAIN;
			}
			else if (mTitle->Draw(s_GameFrameInfo.stepTime ) == Title::SELECT_EXIT) {

				//ゲーム終了へ
				gameMode = GAME_EXIT;
			}
			break;
		case GAME_MAIN:
			//ゲームメイン出力
			mGameMain->Draw( &TInfo ,s_GameFrameInfo.stepTime );
			break;
		case GAME_EXIT:

			Terminate();
			break;
		default:
			break;
		}
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		//現在の時間を取得
		NowTime  = GetNowHiPerformanceCount();

		//前回取得した時間からの経過時間を算出
		s_GameFrameInfo.stepTime = ( NowTime - s_GameFrameInfo.prevTime) / 1000000.0f;

		//状態推移処理を行う回数を算出
		s_GameFrameInfo.stepNum = (int)(s_GameFrameInfo.stepTime / MAX_DELTA_TIME );

		//状態推移処理を行う回数が０回の場合は１回にする
		if (s_GameFrameInfo.stepNum == 0)
		{
			s_GameFrameInfo.stepNum = 1;
		}

		else
		{
			//０回ではない場合は状態推移で進める時間を状態推移を行う回数で割る
			s_GameFrameInfo.stepTime /= s_GameFrameInfo.stepNum;

			//もし状態推移を行う回数が最大値を超えていたら最大値に抑える
			if (s_GameFrameInfo.stepNum > MAX_FRAME_NUM)
			{
				s_GameFrameInfo.stepNum = MAX_FRAME_NUM;
			}
		}

		//今回の時間を保存する
		s_GameFrameInfo.prevTime = NowTime;

		//フレームレート計測用のカウンタを１足す
		s_GameFrameInfo.frameCounter++;

		//前回フレームレートを更新してから１秒経過したら表示用フレームカウントを更新する
		if ( NowTime - s_GameFrameInfo.backDispFrameTime > 1000000)
		{
			//表示用フレームカウントを更新
			s_GameFrameInfo.dispFrameCount = s_GameFrameInfo.frameCounter;

			//計測用フレームカウンタを初期化
			s_GameFrameInfo.frameCounter = 0;

			//表示用フレームカウントを更新した時間を更新
			s_GameFrameInfo.backDispFrameTime = NowTime;
		}

		// 画面を初期化する
		ClearDrawScreen();
	}

}

//後始末処理
void	GameFrame::Terminate() {

	//DXライブラリ終了処理
	DxLib_End();

}