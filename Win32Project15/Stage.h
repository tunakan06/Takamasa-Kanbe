#ifndef _STAGE_H
#define _STAGE_H

#include "DxLib.h"

#include "BinaryFile.h"

// ステージデータに含められる最大キャラ数
#define STAGE_CHARA_MAX_NUM							(256)

// ステージデータに含められる最大オブジェクト数
#define STAGE_OBJECT_MAX_NUM						(512)

// ステージデータに含められる最大オブジェクト用モデル数
#define STAGE_OBJECT_MODEL_MAX_NUM					(256)

// ステージデータに含められる最大イベント数
#define STAGE_EVENT_MAX_NUM							(256)

// 一つのイベント辺りに指定できるオブジェクトの最大数
#define STAGE_EVENT_OBJECT_MAX_NUM					(16)

// コリジョンモデルの最大マテリアル数
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

class Stage {

	//コリジョン用３Ｄモデルハンドル
	int CollisionModelHandle;

	BinaryFile*	mBinaryFile;

	//データ・ポジション格納変数
	int			stagedata;
	int			stagedata_sky;
	int			stagedata_c;

	int			ObjectInfoNum;
	int			ObjectCollisionModelHandle[STAGE_OBJECT_MAX_NUM];

	bool		Load;
	int			ModelHandle;

public:

	//ステージのコリジョン用３Ｄモデルハンドル
	int GetCollisionModelHandle();

	//ステージオブジェクトの数
	int	GetObjectNum();

	//オブジェクトが使用するコリジョン用３Ｄモデルハンドル
	int	GetObjectCollisionModelHandle(int Index);

	//オブジェクトモデルの読み込み
	void	ObjectModel_Load( int Index );

	Stage();

	~Stage();

	//ステージセットアップ
	void	Setup();

	//ステージデータ出力
	int	Draw();

	//角度調整関数
	//float ctArg();

};

#endif
