#ifndef _SOUND_H
#define _SOUND_H

#include "DxLib.h"
#include "TextParam.h"

// ファイルパスの最大長
#define MAX_PATH_LENGTH			64

// １サウンド辺りの最大バリエーション数
#define MAX_HANDLE_NUM			8

// 登録できるサウンドの最大数
#define MAX_SOUNDINFO_NUM		1024

//素材タイプ
typedef enum _EMaterialType
{
	EMaterialType_Grass,	// 草
	EMaterialType_Metal,	// 金属
	EMaterialType_Soil,		// 土
	EMaterialType_Stone,	// 石
	EMaterialType_Wood,		// 木

	EMaterialType_Num		// 素材タイプの数
} EMaterialType;

//BGM
typedef enum _EBGM
{
	EBGM_Stage0,			// ステージ１
	EBGM_Stage1,			// ステージ２
	EBGM_Title,				// タイトル
	EBGM_Boss,				// ボス
	EBGM_GameOver,			// ゲームオーバー
	EBGM_StageClear,		// ステージクリア
	EBGM_AllStageClear,		// 全ステージクリア

	EBGM_Num				// BGMの数
} EBGM;

class Sound {

	//テキストパラメータクラス生成
	TextParam*	mTextParam;

	//サウンドの情報
	struct SSoundInfo
	{
		//３Ｄサウンドかどうか( true:3Dサウンド  false:2Dサウンド )
		bool                 Is3DSound;

		//ファイルパス
		char                 FilePath[MAX_PATH_LENGTH];

		//サウンドハンドルの数
		int                  HandleNum;

		//サウンドハンドル
		int                  Handle[MAX_HANDLE_NUM];
	} sSoundInfo;

	//ＢＧＭの情報
	struct SBgmInfo
	{
		//サウンドハンドル
		int                  SoundHandle;

		//ＢＧＭのループ時に戻る位置
		int                  LoopStartPosition;

		//ＢＧＭのループをする位置
		int                  LoopEndPosition;
	} sBgmInfo;

	//サウンドシステムの情報
	struct _SSoundSystemData
	{
		//サウンドの数
		int                  SoundNum;

		//サウンドの情報
		SSoundInfo           Sound[MAX_SOUNDINFO_NUM];

		//ＢＧＭの情報
		SBgmInfo             Bgm[EBGM_Num];

		//現在鳴らしているＢＧＭ
		EBGM                 NowPlayBgm;
	} sSoundSystemData;

	//サウンドデータ格納変数
	int sounddata[7];

public:

	Sound();

	~Sound();

	//タイトルサウンド出力関数
	void	Output(int i);

	//タイトルサウンド停止関数
	void	stopSound( int i );

	//サウンドファイルを追加する
	int	AddSound(
			//追加するサウンドファイルのパス
			const char* FilePath,
		// ３Ｄで鳴らすサウンドかどうか( true:3Dサウンド  false:2Dサウンド )
		bool Is3DSound
	);

};

#endif
