#ifndef _PLAYER_H
#define _PLAYER_H

#include "DxLib.h"
#include <math.h>
#include "Camera.h"
#include "TextParam.h"
#include "Animation.h"
#include "Sound.h"

class Player{
public:

	//�����񋓌^�ϐ�
	/*enum _Direction
	{
	DOWN,
	LEFT,
	UP,
	RIGHT,
	} direction = UP;*/

	float direction = 2.0;

	//��ԗ񋓌^�ϐ�
	enum State {
		NUTRAL,
		MOVE,
		ATTACK,
	} statenumber;

	//�A�N�V�����񋓌^�ϐ�
	enum Action {
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		NO_ATTACK,
		BLOW,
	} actionnumber;

	//�s��ϐ�
	MATRIX	mat1, mat2;

	//�L�����N�^�[�̏��
	struct PlayerInfo
	{
		//�L�����f�[�^�i�[�ϐ�
		int data;

		//�L�����̗̑�
		int	HP;

		VECTOR TargetMoveDirection;

		float Angle;

	} playerInfo;

	//�L�����ʂ̏����𕪂��邽�߂̃R�[���o�b�N���֐�
	typedef struct _SCharaFunction {




	} SCharaFunction;

	// �L�����̏��
	typedef enum _ECharaState
	{
		ECharaState_Move = 0,						// �ʏ�ړ���
		ECharaState_Attack,							// �U����
		ECharaState_Defence,						// �h�䒆
		ECharaState_Jump,							// �W�����v��
		ECharaState_Damage,							// �_���[�W��
		ECharaState_Blow,							// ������ђ�
		ECharaState_Down,							// �|�ꒆ
		ECharaState_FadeOut,						// �t�F�[�h�A�E�g��
	} ECharaState;


	//�|�W�V�����O�����x�N�g��
	VECTOR	pos = VGet(0.0f, 50.0f, 0.0f);

	//�L�����N�^�[�f�[�^�o��
	void	Draw( float arg, float camX, float camZ, int stg);

	//�A�j���[�V���������֐�
	void	moveAnimation(bool flg, int anim_state);

	//�s���A�j���[�V���������֐�
	void	actionAnimation(bool act, int anim_state);

	//�L�����N�^�[�|�W�V����x���W��Ԃ��֐�
	float	charaPositionX();

	//�L�����N�^�[�|�W�V����z���W��Ԃ��֐�
	float	charaPositionZ();

	//�������̕ϐ��J�ڂ̊֐�
	void	directFunction(float movedir, float camX, float camZ, int stg);

	//�����x�N�g���v�Z
	VECTOR	directVector();

	//�L�����N�^�[�ƃJ�����̊p�x�v�Z
	float	ctArg(float camX, float camZ);

	// �v���C���[�̌�����ς���
	void	AngleProcess();

	//�v���C���[�̈ړ�����
	void	Move( VECTOR MoveVector, int stg );

	void	kill();

	Player();

	~Player();

	bool monsterKill;

private:

	// �ړ��x�N�g���i�[�ϐ�
	VECTOR MVmem = VGet(0.0f,0.0f,0.0f);

	//�L�[�L���ϐ�
	int keymem;

	//����f�[�^�i�[�ϐ�
	int weapondata;

	int sayadata;

	int weaponflm;

	int righthandframeNo;

	int wd;

	int countAnim;

	MATRIX	righthandmatrix;

	//�J��������
	Camera*		mCamera;

	//���퐶��
	//Weapon*		mWeapon;

	//�e�L�X�g�p�����[�^����
	TextParam* mTextParam;

	//�T�E���h����
	Sound*		mSound;

	//�A�j���[�V��������
	Animation*	mAnimation;

	//�ǂݍ��݃j���[�g�����A�j���[�V�����i�[�ϐ�
	int	anim_nutral;

	//���s�A�j���[�V�����i�[�ϐ�
	int	anim_run;

	//�U���A�j���[�V����1�i�[�ϐ�
	int anim_attack_1;

	//�U���A�j���[�V����2�i�[�ϐ�
	int anim_attack_2;

	//�U���A�j���[�V����3�i�[�ϐ�
	int anim_attack_3;

	//�u���E�A�j���[�V����
	int anim_blow_in;

	//
	int	attachidx, rootflm;

	//�A�j���[�V�����g�[�^���^�C��
	float anim_totaltime;

	//�v���C����
	float playtime;

	//���s�t���O�ϐ�
	bool running;

	//�A�N�V�����t���O
	bool action;

	//�L�[����ϐ�
	int	key;

};

#endif
