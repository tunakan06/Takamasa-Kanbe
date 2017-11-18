#ifndef _ENEMY_H
#define _ENEMY_H

#include "DxLib.h"
#include "Monster.h"
#include "Player.h"

//�G�L�������ʃN���X�i�����X�^�[�A�l�Ԃ̓G���ɋ��ʁj
class Enemy {

public:
	Enemy();

	~Enemy();

	//�G����
	void Process( float steotime , VECTOR playerpos);

	//�G�̏����ɕK�v�ȏ��̃Z�b�g�A�b�v
	void InfoSetup(
		VECTOR	charapos,

		//���ڂ����鎞��
		float	StepTime
	);

private:

	bool enemyLive;

	Monster*	mMonster;
	Player*		mPlayer;

	//�G����v���C���[�ւ̃x�N�g��
	VECTOR		EnemyToPlayerVec;
	VECTOR		EnemyToPlayerVec_XZ;

	//�G����v���C���[�ւ̌���
	VECTOR		PlayerDirection;
	VECTOR		PlayerDirection_XZ;

	//�G����v���C���[�܂ł̋���
	float		PlayerDistance;
	float		PlayerDistance_XZ;

	//�v���C���[�ɋC�t�������̃J�E���^�[
	float		PlayerNoticeDiatanceCounter;

	//�G�̎��E�͈̔�
	float		SeeAngleRange;

};

#endif
