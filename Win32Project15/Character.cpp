#include "Character.h"

// 不透明度の変化速度
#define ALPHA_SPEED				3.0f

// 遅れて本来の体力値になる表現の本来の体力値に近づく速度
#define DELAY_PARAM_SPEED		1.0f

// 体力ゲージの体力がある部分の色
#define GAUGE_COLOR_R			220
#define GAUGE_COLOR_G			220
#define GAUGE_COLOR_B			0

// 体力ゲージの体力下無くなった部分の色
#define GAUGE_BASE_COLOR_R		200
#define GAUGE_BASE_COLOR_G		0
#define GAUGE_BASE_COLOR_B		0

// 体力ゲージの減ってしまった部分の色
#define GAUGE_DELAY_COLOR_R		175
#define GAUGE_DELAY_COLOR_G		165
#define GAUGE_DELAY_COLOR_B		0

#define		PI		3.14159

Character::Character() {

	mPlayer = new Player();

	mEnemy = new Enemy();

	mCamera = new Camera();

}

Character::~Character() {

	delete mPlayer;
	mPlayer = 0;

	delete mEnemy;
	mEnemy = 0;

}

//キャラクター処理
void Character::Process( float steptime, int stg ){

	//カメラの座標を返す
	cameraposX = mCamera->cameraPositionX();
	cameraposZ = mCamera->cameraPositionZ();

	//キャラクターとカメラの角度を返す 
	arg = mPlayer->ctArg(cameraposX, cameraposZ);

	//プレイヤーの座標を返す
	playerposX = mPlayer->charaPositionX();
	playerposZ = mPlayer->charaPositionZ();

	//カメラ移動処理
	mCamera->cameraMove(playerposX, playerposZ);

	//カメラ回転処理
	mCamera->cameraRotate(playerposX, playerposZ);

	//キャラクター出力
	mPlayer->Draw( arg , cameraposX, cameraposZ, stg);

	if (mPlayer->monsterKill == false) {
		mEnemy->Process(steptime, mPlayer->pos);
	}

	//mPlayer->directFunction(arg);

}