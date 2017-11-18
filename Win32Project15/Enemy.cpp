#include "Enemy.h"


//�G�쐬
Enemy::Enemy(){

	//�G�̎��E�͈̔͂�ݒ�
	SeeAngleRange = 120.0f;

	mMonster	= new Monster();

	mPlayer = new Player();

	enemyLive = true;

}

Enemy::~Enemy(){

	delete mMonster;
	mMonster = 0;

	delete mPlayer;
	mPlayer = 0;

}

//�G����
void Enemy::Process( float steptime , VECTOR playerpos) {

		mMonster->born(steptime, playerpos);


}

//�G�̏����ɕK�v�ȏ��̃Z�b�g�A�b�v
void Enemy::InfoSetup(VECTOR charapos , float StepTime){

	VECTOR					PlayerHeadPosition;
	VECTOR					HeadPosition;
	int						i;
	MV1_COLL_RESULT_POLY	CollPoly;
	int						StageCOllModel;
	int						StageObjectNum = 21;
	int						ObjectCollModel;

	//�X�e�[�W�I�u�W�F�N�g�̐����擾����

	PlayerNoticeDiatanceCounter = 0.0f;

	//�G����v���C���[�ւ̃x�N�g�����Z�o
	EnemyToPlayerVec		= VSub( mPlayer->pos, charapos );
	EnemyToPlayerVec_XZ	= EnemyToPlayerVec;
	EnemyToPlayerVec_XZ.y	= 0.0f;

	//�G����v���C���[�ւ̐��K���x�N�g�����Z�o
	PlayerDirection = VNorm(EnemyToPlayerVec);
	PlayerDirection_XZ = VNorm(EnemyToPlayerVec_XZ);

	//�G����v���C���[�܂ł̋������Z�o
	PlayerDistance = VSize(EnemyToPlayerVec);
	PlayerDistance_XZ = VSize(EnemyToPlayerVec_XZ);

	//�v���C���[�̂��������ۑ�

	//�v���C���[�ɋC�t�������ɋ���ꍇ�̓v���C���[��
	//�C�t�������ɂȂ��Ă���̎��Ԃ�i�߂�
	if (PlayerDistance < mMonster->noticedistance) {

		PlayerNoticeDiatanceCounter += StepTime;
	
	}
	else {

		PlayerNoticeDiatanceCounter = 0.0f;
		
	}

	//�v���C���[�ɋC�t�������ɋ���ꍇ�̓v���C���[��
	//�C�t�������ɂȂ��Ă���̎��Ԃ�i�߂�( ���������̂ݍl�� )
	if (PlayerDistance_XZ < mMonster->noticedistance) {

		PlayerNoticeDiatanceCounter += StepTime;

	}
	else {

		PlayerNoticeDiatanceCounter = 0.0f;

	}

	//�G�̎��E�͈̔͂Ƀv���C���[�����邩�𒲂ׂ�
	/*if (cos(SeeAngleRange) < VDot(mMonster->FrontDirection, PlayerDirection_XZ)) {

		//�G�̎��E�͈̔͂Ƀv���C���[������ꍇ�͊ԂɎՕ��������Ȃ����𒲂ׂ�

		//�v���C���[�ƓG�̓��̈ʒu���擾
		PlayerHeadPosition	= MV1GetFramePosition( mPlayer->playerInfo.data,
									MV1SearchFrame( mPlayer->playerInfo.data, "head" ));
		HeadPosition = MV1GetFramePosition(mMonster->monsterdata,
									MV1SearchFrame( mMonster->monsterdata, "head" ));

		//���݂��̓����̊ԂɎՂ���̂����邩�ǂ������ׂ�
		//CollPoly = MV1CollCheck_Line( StageCOllModel, -1, HeadPosition,
		//													PlayerHeadPosition);
		//if (CollPoly.HitFlag == FALSE) {
		//	for (i = 0 ; i < StageObjectNum ; i++ ) {
		//	
		//		//ObjectCollModel = 
		//	}
		//
		//}

	}*/

}