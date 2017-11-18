#ifndef _MONSTER_H
#define _MONSTER_H

#include "DxLib.h"
#include "Player.h"
#include "Stage.h"

// �G�P�̕ӂ�̍U���p�^�[���̍ő吔
#define ENEMY_ATTACK_MAX_NUM			(3)

class Monster {

public:

	Monster();

	~Monster();

	//�����X�^�[�`��
	int born( float steptime, VECTOR playerpos);

	//�v���C���[��ǐ�
	void tracking( VECTOR playerpos );

	//�C�Â�����
	float noticedistance;

	//�����X�^�[�f�[�^
	int monsterdata;

	//���̃Z�b�g�A�b�v
	void infoSetup( float steptime, VECTOR playerpos);

	//�����X�^�[�̏�Ԑ���
	//bool step( float steptime );
	
	//�����X�^�[�̈ʒu
	VECTOR pos;

	// �����X�^�[�����t���O
	bool live;

	// �����X�^�[���S�֐�
	void dead();

private:

	// �v���C���[�ȊO�L�������\����
	struct NOTPLAYER
	{
		//CHARA	CharaInfo;					// �L�����N�^�[���
		int			MoveTime;				// �ړ�����
		float		MoveAngle;				// �ړ�����
		VECTOR		TargetMoveDirection;
		float		Angle;
		int			State;
	} np;


	Stage* mStage;

	//�X�e�[�W�p�R���W�����R�c���f���̃n���h��
	int StageCollModel;

	//�X�e�[�W�I�u�W�F�N�g�̐�
	int StageObjectNum;

	//�G����v���C���[�ւ̃x�N�g��
	VECTOR EnemyToPlayerVec;
	VECTOR EnemyToPlayerVec_XZ;

	//�G����v���C���[�ւ̐��K���x�N�g��
	VECTOR PlayerDirection;
	VECTOR PlayerDirection_XZ;

	//�G����v���C���[�܂ł̋���
	float PlayerDistance;
	float PlayerDistance_XZ;

	//���E�͈̔�
	float SeeAngleRange;

	//���݂̌����̐��ʕ����̃x�N�g��
	VECTOR FrontDirection;

	//�v���C���[�ɋC�Â������̃J�E���^
	float PlayerNoticeDistanceCounter;
	float PlayerNoticeDistanceCounter_XZ;

	//�v���C���[�ƓG�̓��̈ʒu
	VECTOR PlayerHeadPosition;
	VECTOR HeadPosition;

	int monster_anim_neutral;

	//�v���C���[�̈ʒu
	VECTOR ppos;

	//���݂��̓����̊ԂɎՂ���̂����邩�ǂ����̕ϐ�
	MV1_COLL_RESULT_POLY	CollPoly;

	//�I�u�W�F�N�g�R���W�������f��
	int		ObjectCollModel;

	//�v���C���[�������邩�𔻕�
	bool	SeePlayer;

	//�v���C���[�������Ă���ꍇ�̃J�E���^
	float	SeePlayerCounter;

	//�I�u�W�F�N�g����
	Player* mPlayer;

	//�v���C���[�����͂ɋ���Ƃ������b�Z�[�W���͂������ǂ���
	bool	PlayerNearDistanceMessage;

	int		AttackNum;
	float	AttackDistance = 500.0;

	bool	AttackDistancebool;
	bool	AttackDistance_XZbool;

	//�C�Â����̔���p�ϐ�
	float	NoticeDistance_See = 2000.0;
	float	NoticeDistance = 300.0;
	float	NoticeDistance_AttackMode = 1000.0;
	float	NoticeTime_See = 1.5;
	float	NoticeTime_Distance = 0.5;

	bool	NoticePlayer;
	bool	NoticePlayer_AttackMode;

};

#endif
