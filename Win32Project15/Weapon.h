#ifndef _WEAPON_H
#define _WEAPON_H

#include "DxLib.h"
#include "TextParam.h"
#include "Sound.h"
#include "Player.h"

//キャラクターの文字列データで使用できる最大文字数
#define CHARA_MAX_STRINGLENGTH			64

class Weapon {

public:

	//キャラクターの武器
	typedef enum _ECharaWeapon
	{
		ECharaWeapon_Sabel,				// サーベル
		ECharaWeapon_Sword,				// 剣
		ECharaWeapon_Axe,				// 斧
		ECharaWeapon_Needle,			// 針
		ECharaWeapon_RockKnuckle,		// 岩殴り

		ECharaWeapon_Num				// キャラクターの武器の数
	} ECharaWeapon;

	//キャラクターの武器の基本情報
	struct SCharaWeaponBaseInfo
	{
		//データファイルが存在するフォルダ名
		char                  DirectoryName[CHARA_MAX_STRINGLENGTH];

		//武器の名前
		char                  Name[CHARA_MAX_STRINGLENGTH];

		//武器の３Ｄモデルハンドル
		int                   ModelHandle;

		//武器が背景の何処に当たっても鳴らす音
		int                   MaterialCommonSound;

		//武器が背景に当たった際に鳴らす素材別の音
		int                   MaterialSound[EMaterialType_Num];
	} sCharaWeaponBaseInfo[ECharaWeapon_Num];

	TextParam*	mTextParam;
	Sound*		mSound;
	Player*		mPlayer;

	const char* weaponstring;

	//武器データ格納変数
	int weapondata;

	int sayadata;

	int weaponflm;

	int righthandframeNo;

	int wd;

	MATRIX	righthandmatrix;

	int model;

	//武器ポジション三次元ベクトル
	VECTOR	wpos = VGet(0.0f, 100.0f, 0.0f);



	Weapon();

	~Weapon();

	//武器出力
	void Draw();

};


#endif

