#include "GameMain.h"

GameMain::GameMain() {

	//メモリ領域の確保
	GMData = (GameMainData*)calloc(1, sizeof(GameMainData));
	if (GMData == NULL) {

		return;
	}



	//ゲームメインの処理を行うかどうかのフラグ
	//GMData->EnableGameMainStepProcess = true;
	//GMData->EnableGameMainRenderProcess = true;

	//ステージデータ生成
	mStage	= new Stage();

	//ステージ開始待ち状態にする
	GMData->State = StageStart_Wait;

	//キャラクタデータ生成
	mCharacter = new Character();
	//mPlayer = new Player();
	//mEnemy = new Enemy();

	//サウンド生成
	//mSound = new Sound();

	//武器データ生成
	//mWeapon = new Weapon();

}

GameMain::~GameMain(){

	delete	mStage;
	mStage	= 0;

	//delete	mEnemy;
	//mEnemy = 0;

	delete	mCharacter;
	mCharacter = 0;

	//delete mWeapon;
	//mWeapon = 0;
	//delete mSound;
	//mSound = 0;

}

//ゲームメイン出力
void	GameMain::Draw( Task::STaskInfo* TInfo ,float steptime ){

	int stage;

	//ステージ出力
	stage = mStage->Draw();

	//キャラクター処理
	mCharacter->Process( steptime, stage );
	//mEnemy->Process( steptime );

	//武器出力
	//mWeapon->Draw();

	//ゲームメインの処理の状態によって処理を分岐
	switch ( GMData->State )
	{
	case	StageStart_Wait:
	
		break;
	}

}