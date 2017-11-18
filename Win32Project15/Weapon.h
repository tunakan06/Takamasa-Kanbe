#ifndef _WEAPON_H
#define _WEAPON_H

#include "DxLib.h"
#include "TextParam.h"
#include "Sound.h"
#include "Player.h"

//�L�����N�^�[�̕�����f�[�^�Ŏg�p�ł���ő啶����
#define CHARA_MAX_STRINGLENGTH			64

class Weapon {

public:

	//�L�����N�^�[�̕���
	typedef enum _ECharaWeapon
	{
		ECharaWeapon_Sabel,				// �T�[�x��
		ECharaWeapon_Sword,				// ��
		ECharaWeapon_Axe,				// ��
		ECharaWeapon_Needle,			// �j
		ECharaWeapon_RockKnuckle,		// �≣��

		ECharaWeapon_Num				// �L�����N�^�[�̕���̐�
	} ECharaWeapon;

	//�L�����N�^�[�̕���̊�{���
	struct SCharaWeaponBaseInfo
	{
		//�f�[�^�t�@�C�������݂���t�H���_��
		char                  DirectoryName[CHARA_MAX_STRINGLENGTH];

		//����̖��O
		char                  Name[CHARA_MAX_STRINGLENGTH];

		//����̂R�c���f���n���h��
		int                   ModelHandle;

		//���킪�w�i�̉����ɓ������Ă��炷��
		int                   MaterialCommonSound;

		//���킪�w�i�ɓ��������ۂɖ炷�f�ޕʂ̉�
		int                   MaterialSound[EMaterialType_Num];
	} sCharaWeaponBaseInfo[ECharaWeapon_Num];

	TextParam*	mTextParam;
	Sound*		mSound;
	Player*		mPlayer;

	const char* weaponstring;

	//����f�[�^�i�[�ϐ�
	int weapondata;

	int sayadata;

	int weaponflm;

	int righthandframeNo;

	int wd;

	MATRIX	righthandmatrix;

	int model;

	//����|�W�V�����O�����x�N�g��
	VECTOR	wpos = VGet(0.0f, 100.0f, 0.0f);



	Weapon();

	~Weapon();

	//����o��
	void Draw();

};


#endif

