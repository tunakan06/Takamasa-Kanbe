#ifndef _SOUND_H
#define _SOUND_H

#include "DxLib.h"
#include "TextParam.h"

// �t�@�C���p�X�̍ő咷
#define MAX_PATH_LENGTH			64

// �P�T�E���h�ӂ�̍ő�o���G�[�V������
#define MAX_HANDLE_NUM			8

// �o�^�ł���T�E���h�̍ő吔
#define MAX_SOUNDINFO_NUM		1024

//�f�ރ^�C�v
typedef enum _EMaterialType
{
	EMaterialType_Grass,	// ��
	EMaterialType_Metal,	// ����
	EMaterialType_Soil,		// �y
	EMaterialType_Stone,	// ��
	EMaterialType_Wood,		// ��

	EMaterialType_Num		// �f�ރ^�C�v�̐�
} EMaterialType;

//BGM
typedef enum _EBGM
{
	EBGM_Stage0,			// �X�e�[�W�P
	EBGM_Stage1,			// �X�e�[�W�Q
	EBGM_Title,				// �^�C�g��
	EBGM_Boss,				// �{�X
	EBGM_GameOver,			// �Q�[���I�[�o�[
	EBGM_StageClear,		// �X�e�[�W�N���A
	EBGM_AllStageClear,		// �S�X�e�[�W�N���A

	EBGM_Num				// BGM�̐�
} EBGM;

class Sound {

	//�e�L�X�g�p�����[�^�N���X����
	TextParam*	mTextParam;

	//�T�E���h�̏��
	struct SSoundInfo
	{
		//�R�c�T�E���h���ǂ���( true:3D�T�E���h  false:2D�T�E���h )
		bool                 Is3DSound;

		//�t�@�C���p�X
		char                 FilePath[MAX_PATH_LENGTH];

		//�T�E���h�n���h���̐�
		int                  HandleNum;

		//�T�E���h�n���h��
		int                  Handle[MAX_HANDLE_NUM];
	} sSoundInfo;

	//�a�f�l�̏��
	struct SBgmInfo
	{
		//�T�E���h�n���h��
		int                  SoundHandle;

		//�a�f�l�̃��[�v���ɖ߂�ʒu
		int                  LoopStartPosition;

		//�a�f�l�̃��[�v������ʒu
		int                  LoopEndPosition;
	} sBgmInfo;

	//�T�E���h�V�X�e���̏��
	struct _SSoundSystemData
	{
		//�T�E���h�̐�
		int                  SoundNum;

		//�T�E���h�̏��
		SSoundInfo           Sound[MAX_SOUNDINFO_NUM];

		//�a�f�l�̏��
		SBgmInfo             Bgm[EBGM_Num];

		//���ݖ炵�Ă���a�f�l
		EBGM                 NowPlayBgm;
	} sSoundSystemData;

	//�T�E���h�f�[�^�i�[�ϐ�
	int sounddata[7];

public:

	Sound();

	~Sound();

	//�^�C�g���T�E���h�o�͊֐�
	void	Output(int i);

	//�^�C�g���T�E���h��~�֐�
	void	stopSound( int i );

	//�T�E���h�t�@�C����ǉ�����
	int	AddSound(
			//�ǉ�����T�E���h�t�@�C���̃p�X
			const char* FilePath,
		// �R�c�Ŗ炷�T�E���h���ǂ���( true:3D�T�E���h  false:2D�T�E���h )
		bool Is3DSound
	);

};

#endif
