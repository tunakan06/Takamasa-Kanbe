#include "GameMain.h"

GameMain::GameMain() {

	//�������̈�̊m��
	GMData = (GameMainData*)calloc(1, sizeof(GameMainData));
	if (GMData == NULL) {

		return;
	}



	//�Q�[�����C���̏������s�����ǂ����̃t���O
	//GMData->EnableGameMainStepProcess = true;
	//GMData->EnableGameMainRenderProcess = true;

	//�X�e�[�W�f�[�^����
	mStage	= new Stage();

	//�X�e�[�W�J�n�҂���Ԃɂ���
	GMData->State = StageStart_Wait;

	//�L�����N�^�f�[�^����
	mCharacter = new Character();
	//mPlayer = new Player();
	//mEnemy = new Enemy();

	//�T�E���h����
	//mSound = new Sound();

	//����f�[�^����
	//mWeapon = new Weapon();

}

GameMain::~GameMain(){

	delete	mStage;
	mStage	= 0;

	//delete	mEnemy;
	//mEnemy = 0;

	delete	mCharacter;
	mCharacter = 0;

	//delete mWeapon;
	//mWeapon = 0;
	//delete mSound;
	//mSound = 0;

}

//�Q�[�����C���o��
void	GameMain::Draw( Task::STaskInfo* TInfo ,float steptime ){

	int stage;

	//�X�e�[�W�o��
	stage = mStage->Draw();

	//�L�����N�^�[����
	mCharacter->Process( steptime, stage );
	//mEnemy->Process( steptime );

	//����o��
	//mWeapon->Draw();

	//�Q�[�����C���̏����̏�Ԃɂ���ď����𕪊�
	switch ( GMData->State )
	{
	case	StageStart_Wait:
	
		break;
	}

}