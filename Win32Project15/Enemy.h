#ifndef _ENEMY_H
#define _ENEMY_H

#include "DxLib.h"
#include "Monster.h"
#include "Player.h"

//敵キャラ共通クラス（モンスター、人間の敵等に共通）
class Enemy {

public:
	Enemy();

	~Enemy();

	//敵処理
	void Process( float steotime , VECTOR playerpos);

	//敵の処理に必要な情報のセットアップ
	void InfoSetup(
		VECTOR	charapos,

		//推移させる時間
		float	StepTime
	);

private:

	bool enemyLive;

	Monster*	mMonster;
	Player*		mPlayer;

	//敵からプレイヤーへのベクトル
	VECTOR		EnemyToPlayerVec;
	VECTOR		EnemyToPlayerVec_XZ;

	//敵からプレイヤーへの向き
	VECTOR		PlayerDirection;
	VECTOR		PlayerDirection_XZ;

	//敵からプレイヤーまでの距離
	float		PlayerDistance;
	float		PlayerDistance_XZ;

	//プレイヤーに気付く距離のカウンター
	float		PlayerNoticeDiatanceCounter;

	//敵の視界の範囲
	float		SeeAngleRange;

};

#endif
