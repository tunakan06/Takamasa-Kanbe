#ifndef _MONSTER_H
#define _MONSTER_H

#include "DxLib.h"
#include "Player.h"
#include "Stage.h"

// 敵１体辺りの攻撃パターンの最大数
#define ENEMY_ATTACK_MAX_NUM			(3)

class Monster {

public:

	Monster();

	~Monster();

	//モンスター描写
	int born( float steptime, VECTOR playerpos);

	//プレイヤーを追跡
	void tracking( VECTOR playerpos );

	//気づく距離
	float noticedistance;

	//モンスターデータ
	int monsterdata;

	//情報のセットアップ
	void infoSetup( float steptime, VECTOR playerpos);

	//モンスターの状態推移
	//bool step( float steptime );
	
	//モンスターの位置
	VECTOR pos;

	// モンスター生存フラグ
	bool live;

	// モンスター死亡関数
	void dead();

private:

	// プレイヤー以外キャラ情報構造体
	struct NOTPLAYER
	{
		//CHARA	CharaInfo;					// キャラクター情報
		int			MoveTime;				// 移動時間
		float		MoveAngle;				// 移動方向
		VECTOR		TargetMoveDirection;
		float		Angle;
		int			State;
	} np;


	Stage* mStage;

	//ステージ用コリジョン３Ｄモデルのハンドル
	int StageCollModel;

	//ステージオブジェクトの数
	int StageObjectNum;

	//敵からプレイヤーへのベクトル
	VECTOR EnemyToPlayerVec;
	VECTOR EnemyToPlayerVec_XZ;

	//敵からプレイヤーへの正規化ベクトル
	VECTOR PlayerDirection;
	VECTOR PlayerDirection_XZ;

	//敵からプレイヤーまでの距離
	float PlayerDistance;
	float PlayerDistance_XZ;

	//視界の範囲
	float SeeAngleRange;

	//現在の向きの正面方向のベクトル
	VECTOR FrontDirection;

	//プレイヤーに気づく距離のカウンタ
	float PlayerNoticeDistanceCounter;
	float PlayerNoticeDistanceCounter_XZ;

	//プレイヤーと敵の頭の位置
	VECTOR PlayerHeadPosition;
	VECTOR HeadPosition;

	int monster_anim_neutral;

	//プレイヤーの位置
	VECTOR ppos;

	//お互いの頭部の間に遮るものがあるかどうかの変数
	MV1_COLL_RESULT_POLY	CollPoly;

	//オブジェクトコリジョンモデル
	int		ObjectCollModel;

	//プレイヤーが見えるかを判別
	bool	SeePlayer;

	//プレイヤーが見えている場合のカウンタ
	float	SeePlayerCounter;

	//オブジェクト生成
	Player* mPlayer;

	//プレイヤーが周囲に居るというメッセージが届いたかどうか
	bool	PlayerNearDistanceMessage;

	int		AttackNum;
	float	AttackDistance = 500.0;

	bool	AttackDistancebool;
	bool	AttackDistance_XZbool;

	//気づく時の判定用変数
	float	NoticeDistance_See = 2000.0;
	float	NoticeDistance = 300.0;
	float	NoticeDistance_AttackMode = 1000.0;
	float	NoticeTime_See = 1.5;
	float	NoticeTime_Distance = 0.5;

	bool	NoticePlayer;
	bool	NoticePlayer_AttackMode;

};

#endif
