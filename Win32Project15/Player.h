#ifndef _PLAYER_H
#define _PLAYER_H

#include "DxLib.h"
#include <math.h>
#include "Camera.h"
#include "TextParam.h"
#include "Animation.h"
#include "Sound.h"

class Player{
public:

	//方向列挙型変数
	/*enum _Direction
	{
	DOWN,
	LEFT,
	UP,
	RIGHT,
	} direction = UP;*/

	float direction = 2.0;

	//状態列挙型変数
	enum State {
		NUTRAL,
		MOVE,
		ATTACK,
	} statenumber;

	//アクション列挙型変数
	enum Action {
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		NO_ATTACK,
		BLOW,
	} actionnumber;

	//行列変数
	MATRIX	mat1, mat2;

	//キャラクターの情報
	struct PlayerInfo
	{
		//キャラデータ格納変数
		int data;

		//キャラの体力
		int	HP;

		VECTOR TargetMoveDirection;

		float Angle;

	} playerInfo;

	//キャラ別の処理を分けるためのコールバック情報関数
	typedef struct _SCharaFunction {




	} SCharaFunction;

	// キャラの状態
	typedef enum _ECharaState
	{
		ECharaState_Move = 0,						// 通常移動中
		ECharaState_Attack,							// 攻撃中
		ECharaState_Defence,						// 防御中
		ECharaState_Jump,							// ジャンプ中
		ECharaState_Damage,							// ダメージ中
		ECharaState_Blow,							// 吹っ飛び中
		ECharaState_Down,							// 倒れ中
		ECharaState_FadeOut,						// フェードアウト中
	} ECharaState;


	//ポジション三次元ベクトル
	VECTOR	pos = VGet(0.0f, 50.0f, 0.0f);

	//キャラクターデータ出力
	void	Draw( float arg, float camX, float camZ, int stg);

	//アニメーション処理関数
	void	moveAnimation(bool flg, int anim_state);

	//行動アニメーション処理関数
	void	actionAnimation(bool act, int anim_state);

	//キャラクターポジションx座標を返す関数
	float	charaPositionX();

	//キャラクターポジションz座標を返す関数
	float	charaPositionZ();

	//方向毎の変数遷移の関数
	void	directFunction(float movedir, float camX, float camZ, int stg);

	//方向ベクトル計算
	VECTOR	directVector();

	//キャラクターとカメラの角度計算
	float	ctArg(float camX, float camZ);

	// プレイヤーの向きを変える
	void	AngleProcess();

	//プレイヤーの移動処理
	void	Move( VECTOR MoveVector, int stg );

	void	kill();

	Player();

	~Player();

	bool monsterKill;

private:

	// 移動ベクトル格納変数
	VECTOR MVmem = VGet(0.0f,0.0f,0.0f);

	//キー記憶変数
	int keymem;

	//武器データ格納変数
	int weapondata;

	int sayadata;

	int weaponflm;

	int righthandframeNo;

	int wd;

	int countAnim;

	MATRIX	righthandmatrix;

	//カメラ生成
	Camera*		mCamera;

	//武器生成
	//Weapon*		mWeapon;

	//テキストパラメータ生成
	TextParam* mTextParam;

	//サウンド生成
	Sound*		mSound;

	//アニメーション生成
	Animation*	mAnimation;

	//読み込みニュートラルアニメーション格納変数
	int	anim_nutral;

	//走行アニメーション格納変数
	int	anim_run;

	//攻撃アニメーション1格納変数
	int anim_attack_1;

	//攻撃アニメーション2格納変数
	int anim_attack_2;

	//攻撃アニメーション3格納変数
	int anim_attack_3;

	//ブロウアニメーション
	int anim_blow_in;

	//
	int	attachidx, rootflm;

	//アニメーショントータルタイム
	float anim_totaltime;

	//プレイ時間
	float playtime;

	//走行フラグ変数
	bool running;

	//アクションフラグ
	bool action;

	//キー操作変数
	int	key;

};

#endif
