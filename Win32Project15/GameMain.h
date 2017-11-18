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

		float	Counter;	//�ėp�J�E���^
		
		//�Q�[�����C���̏�Ԑ��ڏ������s�����ǂ����̃t���O
		bool	EnableGameMainStepProcess;

		//�Q�[�����C���̕`�揈�����s�����ǂ����̃t���O
		bool	EnableGameMainRenderProcess;

		//�v���C���[�̗͕̑\���Ȃǂ��s�����ǂ����̃t���O
		bool	DrawHUD;

	} GameMainData;

	GameMainData*	GMData;

	//�I�u�W�F�N�g�����ϐ�
	Stage*		mStage;
	//Sound*		mSound;
	//�I�u�W�F�N�g�����ϐ�
	Character*	mCharacter;
	//Player*		mPlayer;
	Camera*		mCamera;
	Monster*	mMonster;

	Enemy*		mEnemy;
	Weapon*		mWeapon;

public:

	GameMain();

	~GameMain();

	//�Q�[�����C���f�[�^�o��
	void	Draw( Task::STaskInfo* TInfo, float steptime );

};

#endif
