#include "Enemy.h"


//敵作成
Enemy::Enemy(){

	//敵の視界の範囲を設定
	SeeAngleRange = 120.0f;

	mMonster	= new Monster();

	mPlayer = new Player();

	enemyLive = true;

}

Enemy::~Enemy(){

	delete mMonster;
	mMonster = 0;

	delete mPlayer;
	mPlayer = 0;

}

//敵処理
void Enemy::Process( float steptime , VECTOR playerpos) {

		mMonster->born(steptime, playerpos);


}

//敵の処理に必要な情報のセットアップ
void Enemy::InfoSetup(VECTOR charapos , float StepTime){

	VECTOR					PlayerHeadPosition;
	VECTOR					HeadPosition;
	int						i;
	MV1_COLL_RESULT_POLY	CollPoly;
	int						StageCOllModel;
	int						StageObjectNum = 21;
	int						ObjectCollModel;

	//ステージオブジェクトの数を取得する

	PlayerNoticeDiatanceCounter = 0.0f;

	//敵からプレイヤーへのベクトルを算出
	EnemyToPlayerVec		= VSub( mPlayer->pos, charapos );
	EnemyToPlayerVec_XZ	= EnemyToPlayerVec;
	EnemyToPlayerVec_XZ.y	= 0.0f;

	//敵からプレイヤーへの正規化ベクトルを算出
	PlayerDirection = VNorm(EnemyToPlayerVec);
	PlayerDirection_XZ = VNorm(EnemyToPlayerVec_XZ);

	//敵からプレイヤーまでの距離を算出
	PlayerDistance = VSize(EnemyToPlayerVec);
	PlayerDistance_XZ = VSize(EnemyToPlayerVec_XZ);

	//プレイヤーのいる方向を保存

	//プレイヤーに気付く距離に居る場合はプレイヤーに
	//気付く距離になってからの時間を進める
	if (PlayerDistance < mMonster->noticedistance) {

		PlayerNoticeDiatanceCounter += StepTime;
	
	}
	else {

		PlayerNoticeDiatanceCounter = 0.0f;
		
	}

	//プレイヤーに気付く距離に居る場合はプレイヤーに
	//気付く距離になってからの時間を進める( 水平方向のみ考慮 )
	if (PlayerDistance_XZ < mMonster->noticedistance) {

		PlayerNoticeDiatanceCounter += StepTime;

	}
	else {

		PlayerNoticeDiatanceCounter = 0.0f;

	}

	//敵の視界の範囲にプレイヤーが居るかを調べる
	/*if (cos(SeeAngleRange) < VDot(mMonster->FrontDirection, PlayerDirection_XZ)) {

		//敵の視界の範囲にプレイヤーが居る場合は間に遮蔽物がいないかを調べる

		//プレイヤーと敵の頭の位置を取得
		PlayerHeadPosition	= MV1GetFramePosition( mPlayer->playerInfo.data,
									MV1SearchFrame( mPlayer->playerInfo.data, "head" ));
		HeadPosition = MV1GetFramePosition(mMonster->monsterdata,
									MV1SearchFrame( mMonster->monsterdata, "head" ));

		//お互いの頭部の間に遮るものがあるかどうか調べる
		//CollPoly = MV1CollCheck_Line( StageCOllModel, -1, HeadPosition,
		//													PlayerHeadPosition);
		//if (CollPoly.HitFlag == FALSE) {
		//	for (i = 0 ; i < StageObjectNum ; i++ ) {
		//	
		//		//ObjectCollModel = 
		//	}
		//
		//}

	}*/

}