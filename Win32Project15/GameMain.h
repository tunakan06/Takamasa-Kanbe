#ifndef _GAMEMAIN_H
#define _GAMEMAIN_H

#include "Task.h"
#include "Stage.h"
#include "Character.h"
#include "Camera.h"
#include "Weapon.h"

class GameMain {

	enum GameMainState {
		StageStart_Wait,
		Stage_FadeIn,
		StageNumber,

		GameMainState_Num,
	};

	typedef struct _GameMainData{

		Task::STaskInfo*		TaskInfo;

		GameMainState	State;

		float	Counter;	//汎用カウンタ
		
		//ゲームメインの状態推移処理を行うかどうかのフラグ
		bool	EnableGameMainStepProcess;

		//ゲームメインの描画処理を行うかどうかのフラグ
		bool	EnableGameMainRenderProcess;

		//プレイヤーの体力表示などを行うかどうかのフラグ
		bool	DrawHUD;

	} GameMainData;

	GameMainData*	GMData;

	//オブジェクト生成変数
	Stage*		mStage;
	//Sound*		mSound;
	//オブジェクト生成変数
	Character*	mCharacter;
	//Player*		mPlayer;
	Camera*		mCamera;
	Monster*	mMonster;

	Enemy*		mEnemy;
	Weapon*		mWeapon;

public:

	GameMain();

	~GameMain();

	//ゲームメインデータ出力
	void	Draw( Task::STaskInfo* TInfo, float steptime );

};

#endif
