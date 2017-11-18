#include "Character.h"

// �s�����x�̕ω����x
#define ALPHA_SPEED				3.0f

// �x��Ė{���̗̑͒l�ɂȂ�\���̖{���̗̑͒l�ɋ߂Â����x
#define DELAY_PARAM_SPEED		1.0f

// �̗̓Q�[�W�̗̑͂����镔���̐F
#define GAUGE_COLOR_R			220
#define GAUGE_COLOR_G			220
#define GAUGE_COLOR_B			0

// �̗̓Q�[�W�̗͉̑������Ȃ��������̐F
#define GAUGE_BASE_COLOR_R		200
#define GAUGE_BASE_COLOR_G		0
#define GAUGE_BASE_COLOR_B		0

// �̗̓Q�[�W�̌����Ă��܂��������̐F
#define GAUGE_DELAY_COLOR_R		175
#define GAUGE_DELAY_COLOR_G		165
#define GAUGE_DELAY_COLOR_B		0

#define		PI		3.14159

Character::Character() {

	mPlayer = new Player();

	mEnemy = new Enemy();

	mCamera = new Camera();

}

Character::~Character() {

	delete mPlayer;
	mPlayer = 0;

	delete mEnemy;
	mEnemy = 0;

}

//�L�����N�^�[����
void Character::Process( float steptime, int stg ){

	//�J�����̍��W��Ԃ�
	cameraposX = mCamera->cameraPositionX();
	cameraposZ = mCamera->cameraPositionZ();

	//�L�����N�^�[�ƃJ�����̊p�x��Ԃ� 
	arg = mPlayer->ctArg(cameraposX, cameraposZ);

	//�v���C���[�̍��W��Ԃ�
	playerposX = mPlayer->charaPositionX();
	playerposZ = mPlayer->charaPositionZ();

	//�J�����ړ�����
	mCamera->cameraMove(playerposX, playerposZ);

	//�J������]����
	mCamera->cameraRotate(playerposX, playerposZ);

	//�L�����N�^�[�o��
	mPlayer->Draw( arg , cameraposX, cameraposZ, stg);

	if (mPlayer->monsterKill == false) {
		mEnemy->Process(steptime, mPlayer->pos);
	}

	//mPlayer->directFunction(arg);

}