#include "Title.h"
#include <math.h>

//フォントサイズ
#define		FONT_SIZE			40

//メニュー項目のY座標
#define		MENU_X				530
#define		MENU_Y				450

//メニュー項目の明滅１周にかける時間
#define		MENU_BRINK_TIME		2.0f

//フェードイン時間
#define		FADE_IN_TIME		1.0f

//フェードイン待ち時間
#define		FADE_IN_WAIT_TIME	0.5f

//メニュー項目のフェードイン待ち時間
#define		MENU_IN_WAIT_TIME	0.2f

//メニュー項目のフェードイン時間
#define		MENU_IN_TIME		0.25f

//メニュースペース
#define		MENU_SPACE			64

//タイトル生成
Title::Title() {

	//タイトル画面読み込み
	titleBackGraphic	=	LoadGraph("Data\\2D\\TitleBack.png");

	//ロゴグラフィック読み込み
	logoGraphic			=	LoadGraph("Data\\2D\\Swordbout_logo.png");

	//タイトルサウンドデータ生成
	titlesound = LoadSoundMem("Data\\Sound\\BGM\\BGM_title.ogg");


	//タイトルで使用するフォントの作成
	menuFont = CreateFontToHandle(NULL, FONT_SIZE, 8, DX_FONTTYPE_ANTIALIASING_8X8);

	//タイトルとメニュー項目の不透明度を初期化
	titleOpacity		=	0;
	menuOpacity			=	0;

	//選択項目の明滅用カウンタの初期化
	menuBrinkCounter	=	0;


	//最初の選択状態（New Game）
	selectMode = SELECT_NEW;

	//タイトル遷移状態
	titleState = FADEIN_WAIT;

}

//デストラクタ
Title::~Title() {

	delete& titleBackGraphic;
	titleBackGraphic	=	0;

	delete& logoGraphic;
	logoGraphic			=	0;

}

//モードセレクト処理
void Title::selectModeSequence( SelectMode smode ) {
	
	//モード遷移
	selectMode = smode;
	//待機処理
	WaitTimer(180);

}

//タイトル画面出力
int	Title::Draw(

	//推移させる時間
	float StepTime

) {

	int		i;
	double	t;
	//キー入力変数
	int	key;

	//メニュー項目明滅用カウンタの時間を進める
	menuBrinkCounter += StepTime;
	if (menuBrinkCounter > MENU_BRINK_TIME) {
		menuBrinkCounter -= MENU_BRINK_TIME;
	}

	//タイトル画面出力
	//DrawGraph(0, 0, titleBackGraphic, TRUE);

	//ロゴ画面入力
	//DrawGraph(-40,0, logoGraphic, TRUE);
	

		//キー入力の為の処理
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		//選択状態遷移
		switch (titleState) {

		//フェードイン待ち中
		case	FADEIN_WAIT:
			counter += StepTime;
			//フェードイン待ち時間が経過したらフェードインを開始する
			if (counter > FADE_IN_WAIT_TIME) {
				titleState = FADEIN;
				counter = 0.0f;
			}
			break;
		//フェードイン
		case FADEIN:
			counter += StepTime;
			if (counter > FADE_IN_TIME)
			{
				//フェードインが完了したらメニュー項目フェードイン待ちを開始する
				titleOpacity = 255;
				titleState = MENUIN_WAIT;
				counter = 0.0f;
			}
			else
			{
				//フェードイン中のタイトルの不透明度を算出
				titleOpacity = (int)(counter * 255 / FADE_IN_TIME);
			}
			break;
		case MENUIN_WAIT:		// メニュー項目フェードイン待ち中
			counter += StepTime;
			if (counter > MENU_IN_WAIT_TIME)
			{
				// フェードイン待ち時間が経過したらメニュー項目のフェードインを開始する
				titleState = MENUIN;
				counter = 0.0f;
			}
			break;
		case MENUIN:			// メニュー項目フェードイン中
			counter += StepTime;
			if (counter > MENU_IN_TIME)
			{
				// フェードインが完了したら項目選択を開始する
				menuOpacity = 255;
				titleState = SELECT;
			}
			else
			{
				// フェードイン中のメニュー項目の不透明度を算出
				menuOpacity = (int)(counter * 255 / MENU_IN_TIME);
			}
			break;
		//項目選択中
		case SELECT:
			//タイトルの不透明度が０ではない場合のみタイトルを描画する
			if (titleOpacity > 0)
			{
				//タイトルの背景はタイトルの不透明度に応じて輝度を調節する
				int Bright = titleOpacity * 160 / 255;
				SetDrawBright(Bright / 4, Bright, Bright / 2);
				DrawGraph(0, 0, titleBackGraphic, FALSE);
				SetDrawBright(255, 255, 255);

				//アルファブレンドモードでタイトルの不透明度を設定し、タイトル画像を描画する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleOpacity);
				DrawGraph(0, 0, titleBackGraphic, TRUE);
				//ロゴ画面入力
				DrawGraph(-40, 0, logoGraphic, TRUE);
			}
			//メニュー項目の不透明度が０ではない場合のみメニュー項目を描画する
			if (menuOpacity > 0) {

				//選択している項目の明滅する色の算出
				t = sin(menuBrinkCounter * DX_TWO_PI_F / MENU_BRINK_TIME);
				if (t < 0.0f) t = -t;
				//選択している項目の描画色
				SelectColor = GetColor((int)(t * 128) + 127, 0, 0);

				//通常の描画色の値を取得
				NormalColor = GetColor(255, 255, 255);

				//メニュー項目の数だけ繰り返し
				DrawY = MENU_Y;
				for (i = 0; i < 3; i++) {

					//項目が選択されているかどうかで描画色を変える
					DrawColor = (selectMode == i) ? SelectColor : NormalColor;

					//項目の描画
					DrawStringToHandle(
						MENU_X, DrawY, g_TitleMenuTable[i], DrawColor, menuFont);
					// 項目の描画Y座標を１項目分下に移動する
					DrawY += MENU_SPACE;
				}

				switch (selectMode) {
				case	SELECT_NEW:
					//モード選択
					if (key & PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_CONTINUE);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_EXIT);
					}
					//モード決定
					if (key & PAD_INPUT_1) {
						//ニューゲームへ移行
						return	SELECT_NEW;
					}
					break;
				case	SELECT_CONTINUE:
					if (key & PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_EXIT);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_NEW);
					}
					if (key & PAD_INPUT_1) {
						//ゲームコンティニューへ移行
						return SELECT_CONTINUE;
					}
					break;
				case	SELECT_EXIT:
					if (key &PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_NEW);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_CONTINUE);
					}
					//モード決定
					if (key & PAD_INPUT_1) {
						//ゲームを終える
						return SELECT_EXIT;
					}
					break;
				}
			}
		}
	return SELECT_MODE_NONE;
}

//タイトル画面後始末
void Title::Terminate() {

	//タイトル画面の削除
	DeleteGraph( titleBackGraphic );

	//ロゴの削除
	DeleteGraph( logoGraphic );

	//メニューフォントの削除
	DeleteFontToHandle( menuFont );

}