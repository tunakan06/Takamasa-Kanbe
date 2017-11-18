#include "Player.h"

#include "Monster.h"

#define PLAYER_MOVE_SPEED			30.0f*3.0f*3.0f		// �ړ����x
#define PLAYER_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
#define PLAYER_ENUM_DEFAULT_SIZE		800.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define PLAYER_HIT_WIDTH			200.0f		// �����蔻��J�v�Z���̔��a
#define PLAYER_HIT_HEIGHT			700.0f		// �����蔻��J�v�Z���̍���
#define PLAYER_HIT_TRYNUM			16		// �ǉ����o�������̍ő厎�s��
#define PLAYER_HIT_SLIDE_LENGTH			5.0f		// ��x�̕ǉ����o�������ŃX���C�h�����鋗��

Player::Player(){

	//���s�t���O�B�ŏ��͋U
	running = false;

	//�A�N�V�����t���O�B�ŏ��͋U
	action = false;

	playtime = 0.0f;

	//�e�L�X�g�p�����[�^����
	mTextParam = new TextParam();

	//�T�E���h����
	mSound = new Sound();

	//���퐶��
	//mWeapon = new Weapon();

	//�A�j���[�V��������
	mAnimation = new Animation();

	//�v���C���[�f�[�^���[�h
	playerInfo.data = MV1LoadModel("Data\\Character\\Player\\PC.mv1");

	//�j���[�g�����A�j���[�V�������[�h
	anim_nutral = MV1LoadModel("Data\\Character\\Player\\Anim_Neutral.mv1");

	//���s�A�j���[�V����
	anim_run = MV1LoadModel("Data\\Character\\Player\\Anim_Run.mv1");
	
	//if(MV1SetScale(playerInfo.data, VGet( 10,10, 10)) == -1) printfDx("���f���̓ǂݍ��݂Ɏ��s");

	//�U���A�j���[�V����1
	anim_attack_1 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack1.mv1");

	//�U���A�j���[�V����2
	anim_attack_2 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack2.mv1");

	//�U���A�j���[�V����3
	anim_attack_3 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack3.mv1");

	//�u���E�A�j���[�V����
	anim_blow_in = MV1LoadModel("Data\\Character\\Player\\Anim_Blow_In.mv1");

	//�A�^�b�`�i���t���j
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_nutral);

	//�A�j���[�V�������v����
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);

	//
	rootflm = MV1SearchFrame(playerInfo.data, "root");

	//
	MV1SetFrameUserLocalMatrix(playerInfo.data, rootflm, MGetIdent());

	weapondata = MV1LoadModel("Data\\Character\\Player\\Sabel.mv1");

	sayadata = MV1LoadModel("Data\\Character\\Player\\Saya.mv1");

	righthandframeNo = MV1SearchFrame(playerInfo.data, "wp");

	actionnumber = NO_ATTACK;

	playerInfo.Angle = 0.0f;

	playerInfo.TargetMoveDirection = VGet( 1.0f, 0.0f, 0.0f );

	countAnim = 0;

	monsterKill = false;

}

Player::~Player(){

	delete& playerInfo.data;
	playerInfo.data = 0;

	delete& anim_nutral;
	anim_nutral = 0;

	delete& anim_run;
	anim_run = 0;

}

//�L�����N�^�[�o��
void	Player::Draw( float arg, float camX, float camZ, int stg) {

	if (countAnim > 3 * 60) {
		countAnim = 0;
	}

	//�A�j���[�V�����i�s
	playtime += 0.5f;
	if (playtime > anim_totaltime) playtime = 0.0f;
	MV1SetAttachAnimTime(playerInfo.data, attachidx, playtime);

	//�L�[����
	key = GetJoypadInputState(DX_INPUT_KEY);


	//�A�j���[�V�������̕ϐ��J��
	if (key & PAD_INPUT_A) { actionnumber = ATTACK_1; }
	if (key & PAD_INPUT_B) { actionnumber = BLOW; }

	//�A�j���[�V����	
	if (key == 0) {
		if (running == true) {
			moveAnimation(false, anim_nutral);
		}
		else if (action == true) {
			actionAnimation(false, anim_nutral);
		}
	}
	else {
		if (((key & PAD_INPUT_DOWN) || (key & PAD_INPUT_UP) || (key & PAD_INPUT_LEFT) || (key & PAD_INPUT_RIGHT)) && (running == false)) {
			moveAnimation(true, anim_run);
		}
		else if (((key & PAD_INPUT_A) || (key & PAD_INPUT_B)) && (action == false)) {
			actionAnimation(true, anim_attack_1);
			if ( VSize( VSub(pos,Monster().pos)) < 30.0f ) {
				// �G������
				kill();

			}
			actionnumber = ATTACK_1;
			countAnim++;
			//WaitTimer(120);
			if ((key & PAD_INPUT_A)&&(actionnumber == ATTACK_1) && (action == true)) {
			actionAnimation(true, anim_attack_2);
			actionnumber = ATTACK_2;
			countAnim++;
			//WaitTimer(120);
				if ((key & PAD_INPUT_A) && (actionnumber == ATTACK_2) && (action == true)) {
					actionAnimation(true, anim_attack_3);
					actionnumber = ATTACK_3;
					countAnim++;
					//WaitTimer(120);
				}
			}
			if (countAnim > 60*2*5*100 ) {
				actionnumber = NO_ATTACK;
			}
		}
	}
	//�������̕ϐ��J��
	directFunction(arg, camX, camZ, stg);

	//ClearDrawScreen();
	
	//�L�����N�^�[��]�s�񉉎Z
	MV1SetRotationXYZ(playerInfo.data, VGet(0.f, playerInfo.Angle + DX_PI_F, 0.f));
	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(playerInfo.data, pos);
	//mat1 = MGetRotY( playerInfo.Angle + DX_PI_F );
	//mat2 = MGetTranslate(pos);
	//MV1SetMatrix(playerInfo.data, MMult(mat1, mat2));

	//�L�����N�^�[�o��
	MV1DrawModel(playerInfo.data);

	//����ݒ�
	wd = weapondata;

	//�L�����N�^�[���f���̉E��t���[���̍s����擾
	righthandmatrix = MV1GetFrameLocalWorldMatrix(playerInfo.data, righthandframeNo);
	// �L�����N�^�[���f���̉E��t���[���̍s����A�N�Z�T�����f���̍s��Ƃ��ăZ�b�g���Ă���`��
	MV1SetMatrix(wd, righthandmatrix);
	//����R�c���f����`��
	MV1DrawModel(wd);


}

//�ړ��A�j���[�V���������֐�
void	Player::moveAnimation(bool flg, int anim_state) {

	running = flg;
	if (attachidx >= 0) {
		MV1DetachAnim(playerInfo.data, attachidx);
	}
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_state);
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);

}

//�s���A�j���[�V���������֐�
void	Player::actionAnimation(bool act, int anim_state) {

	action = act;
	if ( attachidx >= 0 ) {
		MV1DetachAnim(playerInfo.data, attachidx);
	}
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_state);
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);
}

//�L�����N�^�[�|�W�V����x���W��Ԃ��֐�
float	Player::charaPositionX() {

	return pos.x;

}

//�L�����N�^�[�|�W�V����z���W��Ԃ��֐�
float	Player::charaPositionZ() {

	return pos.z;

}

//�������̕ϐ��J�ڂ̊֐�
void	Player::directFunction(float movedir, float camX, float camZ, int stg) {

	VECTOR CamVec = VGet(camX, 0, camZ);

	VECTOR UpMoveVec;
	VECTOR LeftMoveVec;
	VECTOR MoveVec;

	UpMoveVec = VSub( pos , CamVec );
	UpMoveVec.y = 0.0f;

	LeftMoveVec = VCross(UpMoveVec, VGet(0.0f, 1.0f, 0.0f));

	UpMoveVec = VNorm(UpMoveVec);
	LeftMoveVec = VNorm(LeftMoveVec);

	// ���̃t���[���ł̈ړ��x�N�g����������
	MoveVec = VGet(0.0f, 0.0f, 0.0f);

	if (key & PAD_INPUT_DOWN) {
		MoveVec = VAdd(MoveVec, VScale(UpMoveVec, -1.0f)); //direction = 0.0 + di;
		MVmem = MoveVec;
	}
	else 
	if (key & PAD_INPUT_UP) {
		MoveVec = VAdd(MoveVec, UpMoveVec); //direction = 2.0 + di;
		MVmem = MoveVec;
	}
	if (key & PAD_INPUT_LEFT) {
		MoveVec = VAdd(MoveVec, LeftMoveVec); //direction = 1.0 + di;
		MVmem = MoveVec;
	}
	else
	if (key & PAD_INPUT_RIGHT) {
		MoveVec = VAdd(MoveVec, VScale(LeftMoveVec, -1.0f)); //direction = -1.0 + di;
		MVmem = MoveVec;
	}

	playerInfo.TargetMoveDirection = VNorm(MVmem);

	// �v���C���[�̌�����ς���
	AngleProcess();

	// �ړ��x�N�g�������ɃR���W�������l�����v���C���[���ړ�
	Move(MoveVec, stg);

	// �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
	MoveVec = VScale(playerInfo.TargetMoveDirection, 6000.0f * PLAYER_MOVE_SPEED);

}

//�����x�N�g���v�Z
VECTOR	Player::directVector() {

	return	VGet(pos.x, pos.y, pos.z);

}

//�L�����N�^�[�ƃJ�����̊p�x�v�Z
float Player::ctArg(float camX, float camZ) {

	return (float)atan((pos.z - camZ) / (pos.x - camX));

}

// �v���C���[�̌�����ς���
void Player::AngleProcess(){
	float TargetAngle;			// �ڕW�p�x
	float SaAngle;				// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

								// �ڕW�̕����x�N�g������p�x�l���Z�o����
	TargetAngle = atan2(playerInfo.TargetMoveDirection.x, playerInfo.TargetMoveDirection.z);

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	{
		// �ŏ��͒P���Ɉ����Z
		SaAngle = TargetAngle - playerInfo.Angle;

		// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
		// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
		if (SaAngle < -DX_PI_F)
		{
			SaAngle += DX_TWO_PI_F;
		}
		else
			if (SaAngle > DX_PI_F)
			{
				SaAngle -= DX_TWO_PI_F;
			}
	}

	// �p�x�̍����O�ɋ߂Â���
	if (SaAngle > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		SaAngle -= 0.2f;
		if (SaAngle < 0.0f)
		{
			SaAngle = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		SaAngle += 0.2f;
		if (SaAngle > 0.0f)
		{
			SaAngle = 0.0f;
		}
	}

	// ���f���̊p�x���X�V
	playerInfo.Angle = TargetAngle - SaAngle;
}


// �v���C���[�̈ړ�����
void Player::Move(VECTOR MoveVector, int stg) {

	int i, j, k;						// �ėp�J�E���^�ϐ�
	int MoveFlag;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
	int HitFlag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
	MV1_COLL_RESULT_POLY_DIM HitDim;			// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int KabeNum;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int YukaNum;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY *Kabe[PLAYER_MAX_HITCOLL];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY *Yuka[PLAYER_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY *Poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	HITRESULT_LINE LineRes;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
	VECTOR OldPos;						// �ړ��O�̍��W	
	VECTOR NowPos;						// �ړ���̍��W

										// �ړ��O�̍��W��ۑ�
	OldPos = pos;

	// �ړ���̍��W���Z�o
	NowPos = VAdd(pos, MoveVector);

	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ( ���o����͈͈͂ړ��������l������ )
	HitDim = MV1CollCheck_Sphere(stg, -1, pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));

	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		MoveFlag = 1;
	}
	else
	{
		MoveFlag = 0;
	}

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
	{
		// �ǃ|���S���Ə��|���S���̐�������������
		KabeNum = 0;
		YukaNum = 0;

		// ���o���ꂽ�|���S���̐������J��Ԃ�
		for (i = 0; i < HitDim.HitNum; i++)
		{
			// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
			if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f)
			{
				// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
				if (HitDim.Dim[i].Position[0].y > pos.y + 1.0f ||
					HitDim.Dim[i].Position[1].y > pos.y + 1.0f ||
					HitDim.Dim[i].Position[2].y > pos.y + 1.0f)
				{
					// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
					if (KabeNum < PLAYER_MAX_HITCOLL)
					{
						// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
						Kabe[KabeNum] = &HitDim.Dim[i];

						// �ǃ|���S���̐������Z����
						KabeNum++;
					}
				}
			}
			else
			{
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (YukaNum < PLAYER_MAX_HITCOLL)
				{
					// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
					Yuka[YukaNum] = &HitDim.Dim[i];

					// ���|���S���̐������Z����
					YukaNum++;
				}
			}
		}
	}

	// �ǃ|���S���Ƃ̓����蔻�菈��
	if (KabeNum != 0)
	{
		// �ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		HitFlag = 0;

		// �ړ��������ǂ����ŏ����𕪊�
		if (MoveFlag == 1)
		{
			// �ǃ|���S���̐������J��Ԃ�
			for (i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];

				// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
				{
					VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��

										// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
					SlideVec = VCross(MoveVector, Poly->Normal);

					// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
					// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
					SlideVec = VCross(Poly->Normal, SlideVec);

					// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
					NowPos = VAdd(OldPos, SlideVec);
				}

				// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				for (j = 0; j < KabeNum; j++)
				{
					// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[j];

					// �������Ă����烋�[�v���甲����
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
				}

				// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				// �ǂɓ��������t���O��|������Ń��[�v���甲����
				if (j == KabeNum)
				{
					HitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for (i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];

				// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					HitFlag = 1;
					break;
				}
			}
		}

		// �ǂɓ������Ă�����ǂ��牟���o���������s��
		if (HitFlag == 1)
		{
			// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (k = 0; k < PLAYER_HIT_TRYNUM; k++)
			{
				// �ǃ|���S���̐������J��Ԃ�
				for (i = 0; i < KabeNum; i++)
				{
					// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[i];

					// �v���C���[�Ɠ������Ă��邩�𔻒�
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					NowPos = VAdd(NowPos, VScale(Poly->Normal, PLAYER_HIT_SLIDE_LENGTH));

					// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < KabeNum; j++)
					{
						// �������Ă����烋�[�v�𔲂���
						Poly = Kabe[j];
						if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
					if (j == KabeNum) break;
				}

				// i �� KabeNum �ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɑS�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != KabeNum) break;
			}
		}
	}

	// ���|���S���Ƃ̓����蔻��
	if (YukaNum != 0)
	{
		// �W�����v�����㏸���̏ꍇ�͏����𕪊�
		//if (pl.State == 2 && pl.JumpPower > 0.0f)
		/*{
			float MinY;

			// �V��ɓ����Ԃ��鏈�����s��

			// ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ���������
			MinY = 0.0f;

			// �����������ǂ����̃t���O�𓖂����Ă��Ȃ����Ӗ�����O�ɂ��Ă���
			HitFlag = 0;

			// ���|���S���̐������J��Ԃ�
			for (i = 0; i < YukaNum; i++)
			{
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[i];

				// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
				LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

				// �ڐG���Ă��Ȃ������牽�����Ȃ�
				if (LineRes.HitFlag == FALSE) continue;

				// ���Ƀ|���S���ɓ������Ă��āA�����܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
				if (HitFlag == 1 && MinY < LineRes.Position.y) continue;

				// �|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ڐG�����x���W��ۑ�����
				MinY = LineRes.Position.y;
			}

			// �ڐG�����|���S�������������ǂ����ŏ����𕪊�
			if (HitFlag == 1)
			{
				// �ڐG�����ꍇ�̓v���C���[�̂x���W��ڐG���W�����ɍX�V
				NowPos.y = MinY - PLAYER_HIT_HEIGHT;

				// �x�������̑��x�͔��]
				//pl.JumpPower = -pl.JumpPower;
			}
		}*/
		//else
		{
			float MaxY;

			// ���~�����W�����v���ł͂Ȃ��ꍇ�̏���

			// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
			HitFlag = 0;

			// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
			MaxY = 0.0f;

			// ���|���S���̐������J��Ԃ�
			for (i = 0; i < YukaNum; i++)
			{
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[i];

				// �W�����v�����ǂ����ŏ����𕪊�
				/*if (pl.State == 2)
				{
					// �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}*/
				//else
				{
					// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}

				// �������Ă��Ȃ������牽�����Ȃ�
				if (LineRes.HitFlag == FALSE) continue;

				// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
				if (HitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// �|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1;

				// �ڐG�����x���W��ۑ�����
				MaxY = LineRes.Position.y;
			}

			// ���|���S���ɓ����������ǂ����ŏ����𕪊�
			if (HitFlag == 1)
			{
				// ���������ꍇ

				// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
				NowPos.y = MaxY;

				// �x�������̈ړ����x�͂O��
				//pl.JumpPower = 0.0f;

				// �����W�����v���������ꍇ�͒��n��Ԃɂ���
				/*if (pl.State == 2)
				{
					// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
					if (MoveFlag)
					{
						// �ړ����Ă���ꍇ�͑����Ԃ�
						Player_PlayAnim(1);
						pl.State = 1;
					}
					else
					{
						// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
						Player_PlayAnim(4);
						pl.State = 0;
					}

					// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
					pl.AnimBlendRate = 1.0f;
				}*/
			}
			else
			{
				// ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
				//if (pl.State != 2)
				{
					// �W�����v���ɂ���
					//pl.State = 2;

					// ������Ƃ����W�����v����
					//pl.JumpPower = PLAYER_FALL_UP_POWER;

					// �A�j���[�V�����͗������̂��̂ɂ���
					//Player_PlayAnim(3);
				}
			}
		}
	}

	// �V�������W��ۑ�����
	pos = NowPos;

	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(playerInfo.data, pos);

	// ���o�����v���C���[�̎��͂̃|���S�������J������
	MV1CollResultPolyDimTerminate(HitDim);

}

void Player::kill() {

	monsterKill = true;

}