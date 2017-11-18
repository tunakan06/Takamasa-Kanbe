#include "Monster.h"
#include <math.h>

#define CHARA_MOVE_SPEED			30.0f		// �ړ����x
#define CHARA_ANGLE_SPEED			0.2f		// �p�x�ω����x

// �v���C���[�L�����ȊO�L�����̏��
#define NOTPLAYER_NUM				4			// �v���C���[�ȊO�̃L�����̐�
#define NOTPLAYER_MOVETIME			120			// ��̕����Ɉړ����鎞��
#define NOTPLAYER_JUMPRATIO			250			// �v���C���[�ȊO�̃L�������W�����v����m��

Monster::Monster(){

	mPlayer = new Player();
	mStage	= new Stage();

	noticedistance	= 300.0f;

	//�����X�^�[�i�I�j�f�[�^���[�h
	monsterdata		=	MV1LoadModel("Data\\Character\\Bee\\Bee.mv1");

	//�����X�^�[�j���[�g�������[�h
	monster_anim_neutral = MV1LoadModel("Data\\Character\\Bee\\Anim_Neutral.mv1");

	//�����ʒu
	pos = VGet( 0.0f, 200.0f, 500.0f);

	//�v���C���[�ɋC�Â�����
	PlayerNoticeDistanceCounter = 0.0f;
	PlayerNoticeDistanceCounter_XZ = 0.0f;

	//���E�͈̔�
	SeeAngleRange = 120.0f * DX_PI_F / 180.0f;

	int	i;

	for (i = 0; i < ENEMY_ATTACK_MAX_NUM; i++)
	{
		AttackNum++;
	}

	np.State = 0;

}

Monster::~Monster(){
}

//�����X�^�[�`��
int Monster::born( float steptime, VECTOR playerpos) {

	int i;
	int j;
	VECTOR MoveVec;
	//int JumpFlag;

	// �L�����N�^�̐������J��Ԃ�
	for (i = 0; i < NOTPLAYER_NUM; i++)
	{
		// �W�����v�t���O��|���Ă���
		//JumpFlag = 0;

		// ��莞�Ԃ��o�߂�����ړ����������ύX����
		np.MoveTime++;
		if (np.MoveTime >= NOTPLAYER_MOVETIME)
		{
			np.MoveTime = 0;

			// �V���������̌���
			np.MoveAngle = GetRand(1000) * DX_PI_F * 2.0f / 1000.0f;

			// ���m���ŃW�����v�@�@�@����
			if (GetRand(1000) < NOTPLAYER_JUMPRATIO)
			{
				//JumpFlag = 1;
			}
		}

		// �V���������̊p�x����x�N�g�����Z�o
		MoveVec.x = cos(np.MoveAngle) * CHARA_MOVE_SPEED/60.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = sin(np.MoveAngle) * CHARA_MOVE_SPEED/60.0f;

		// �v���C���[�Ƃ̓����蔻����s��
		//Chara_Collision(&npl[i].CharaInfo, &MoveVec, &pl.CharaInfo);

		// �����ȊO�̃v���C���[�L�����Ƃ̓����蔻����s��
		for (j = 0; j < NOTPLAYER_NUM; j++)
		{
			// �����Ƃ̓����蔻��͂��Ȃ�
			if (i == j) continue;

			//Chara_Collision(&npl[i].CharaInfo, &MoveVec, &npl[j].CharaInfo);
		}

		// �ړ��������s��
		//Chara_Process(&npl[i].CharaInfo, MoveVec, JumpFlag);
		{
			int MoveFlag;			// �ړ��������ǂ����̃t���O( 1:�ړ�����  0:�ړ����Ă��Ȃ� )

			// �ړ��������ǂ����̃t���O���Z�b�g�A�����ł��ړ����Ă�����u�ړ����Ă���v��\���P�ɂ���
			MoveFlag = 0;
			if (MoveVec.x < -0.001f || MoveVec.x > 0.001f ||
				MoveVec.y < -0.001f || MoveVec.y > 0.001f ||
				MoveVec.z < -0.001f || MoveVec.z > 0.001f)
			{
				MoveFlag = 1;
			}

			// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
			if (MoveFlag)
			{
				// �ړ��x�N�g���𐳋K���������̂��L�����N�^�[�������ׂ������Ƃ��ĕۑ�
				np.TargetMoveDirection = VNorm(MoveVec);

				// �������܂Łu�����~�܂�v��Ԃ�������
				if (np.State == 0)
				{
					// ����A�j���[�V�������Đ�����
					//Chara_PlayAnim(ch, 1);

					// ��Ԃ��u����v�ɂ���
					np.State = 1;
				}
			}
			else
			{
				// ���̃t���[���ňړ����Ă��Ȃ��āA����Ԃ��u����v��������
				if (np.State == 1)
				{
					// �����~��A�j���[�V�������Đ�����
					//Chara_PlayAnim(ch, 4);

					// ��Ԃ��u�����~��v�ɂ���
					np.State = 0;
				}
			}

			// �L�����N�^�[�̈ړ������Ƀ��f���̕������߂Â���
			//Chara_AngleProcess(ch);
			{
				float TargetAngle;			// �ڕW�p�x
				float SaAngle;				// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

											// �ڕW�̕����x�N�g������p�x�l���Z�o����
				TargetAngle = atan2(np.TargetMoveDirection.x, np.TargetMoveDirection.z);

				// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
				{
					// �ŏ��͒P���Ɉ����Z
					SaAngle = TargetAngle - np.Angle;

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
					SaAngle -= CHARA_ANGLE_SPEED;
					if (SaAngle < 0.0f)
					{
						SaAngle = 0.0f;
					}
				}
				else
				{
					// �����}�C�i�X�̏ꍇ�͑���
					SaAngle += CHARA_ANGLE_SPEED;
					if (SaAngle > 0.0f)
					{
						SaAngle = 0.0f;
					}
				}

				// ���f���̊p�x���X�V
				np.Angle = TargetAngle - SaAngle;
				MV1SetRotationXYZ(monsterdata, VGet(0.0f, np.Angle + DX_PI_F, 0.0f));
			}

			// �ړ��x�N�g�������ɃR���W�������l�����L�����N�^�[���ړ�
			//Chara_Move(ch, MoveVec);
			{
				int i, j, k;						// �ėp�J�E���^�ϐ�
				int MoveFlag;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
				int HitFlag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
				MV1_COLL_RESULT_POLY_DIM HitDim;			// �L�����N�^�[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
				int KabeNum;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
				int YukaNum;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
			//	MV1_COLL_RESULT_POLY *Kabe[CHARA_MAX_HITCOLL];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
			//	MV1_COLL_RESULT_POLY *Yuka[CHARA_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
				MV1_COLL_RESULT_POLY *Poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
				HITRESULT_LINE LineRes;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
				VECTOR OldPos;						// �ړ��O�̍��W	
				VECTOR NowPos;						// �ړ���̍��W

													// �ړ��O�̍��W��ۑ�
				OldPos = pos;

				// �ړ���̍��W���Z�o
				NowPos = VAdd(pos, MoveVec);

				// �L�����N�^�[�̎��͂ɂ���X�e�[�W�|���S�����擾����
				// ( ���o����͈͈͂ړ��������l������ )
				/*HitDim = MV1CollCheck_Sphere(stg.ModelHandle, -1, ch->Position, CHARA_ENUM_DEFAULT_SIZE + VSize(MoveVector));

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
							// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�L�����N�^�[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
							if (HitDim.Dim[i].Position[0].y > ch->Position.y + 1.0f ||
								HitDim.Dim[i].Position[1].y > ch->Position.y + 1.0f ||
								HitDim.Dim[i].Position[2].y > ch->Position.y + 1.0f)
							{
								// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
								if (KabeNum < CHARA_MAX_HITCOLL)
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
							if (YukaNum < CHARA_MAX_HITCOLL)
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

							// �|���S���ƃL�����N�^�[���������Ă��Ȃ������玟�̃J�E���g��
							if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

							// �����ɂ�����|���S���ƃL�����N�^�[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
							HitFlag = 1;

							// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
							{
								VECTOR SlideVec;	// �L�����N�^�[���X���C�h������x�N�g��

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
								if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
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
							if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
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
						for (k = 0; k < CHARA_HIT_TRYNUM; k++)
						{
							// �ǃ|���S���̐������J��Ԃ�
							for (i = 0; i < KabeNum; i++)
							{
								// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
								Poly = Kabe[i];

								// �L�����N�^�[�Ɠ������Ă��邩�𔻒�
								if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

								// �������Ă�����K�苗�����L�����N�^�[��ǂ̖@�������Ɉړ�������
								NowPos = VAdd(NowPos, VScale(Poly->Normal, CHARA_HIT_SLIDE_LENGTH));

								// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
								for (j = 0; j < KabeNum; j++)
								{
									// �������Ă����烋�[�v�𔲂���
									Poly = Kabe[j];
									if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
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
					if (ch->State == 2 && ch->JumpPower > 0.0f)
					{
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
							LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

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
							// �ڐG�����ꍇ�̓L�����N�^�[�̂x���W��ڐG���W�����ɍX�V
							NowPos.y = MinY - CHARA_HIT_HEIGHT;

							// �x�������̑��x�͔��]
							ch->JumpPower = -ch->JumpPower;
						}
					}
					else
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
							if (ch->State == 2)
							{
								// �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
								LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
							}
							else
							{
								// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
								LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
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

							// �ڐG�����|���S���ň�ԍ����x���W���L�����N�^�[�̂x���W�ɂ���
							NowPos.y = MaxY;

							// �x�������̈ړ����x�͂O��
							ch->JumpPower = 0.0f;

							// �����W�����v���������ꍇ�͒��n��Ԃɂ���
							if (ch->State == 2)
							{
								// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
								if (MoveFlag)
								{
									// �ړ����Ă���ꍇ�͑����Ԃ�
									Chara_PlayAnim(ch, 1);
									ch->State = 1;
								}
								else
								{
									// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
									Chara_PlayAnim(ch, 4);
									ch->State = 0;
								}

								// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
								ch->AnimBlendRate = 1.0f;
							}
						}
						else
						{
							// ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
							if (ch->State != 2)
							{
								// �W�����v���ɂ���
								ch->State = 2;

								// ������Ƃ����W�����v����
								ch->JumpPower = CHARA_FALL_UP_POWER;

								// �A�j���[�V�����͗������̂��̂ɂ���
								Chara_PlayAnim(ch, 3);
							}
						}
					}
				}*/

				// �V�������W��ۑ�����
				pos = NowPos;

				// �L�����N�^�[�̃��f���̍��W���X�V����
				MV1SetPosition(monsterdata, pos);

				// ���o�����L�����N�^�[�̎��͂̃|���S�������J������
				//MV1CollResultPolyDimTerminate(HitDim);
			}

			// �A�j���[�V��������
			//Chara_AnimProcess(ch);
		}

	}

	//�G�̏����ɕK�v�ȏ��̃Z�b�g�A�b�v
	infoSetup( steptime , playerpos);

	//�����X�^�[�ʒu�ݒ�
	MV1SetPosition( monsterdata, pos );

	//�����X�^�[�j���[�g�����A�j���[�V����
	MV1AttachAnim( monsterdata,0,monster_anim_neutral );

	//�����X�^�[�`��
	MV1DrawModel( monsterdata );

	//�����X�^�[���v���C���[����������A�v���C���[��ǐ�
	//tracking(playerpos);

	return monsterdata;

}

//�v���C���[��ǐ�
void Monster::tracking(	VECTOR playerpos ) {

	char *a;

	//�v���C���[�̈ʒu���i�[
	//ppos = mPlayer->pos;

	//�f�o�b�O
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawFormatString(1280 - 84, 720 - 20, GetColor(255, 255, 255), "pos.x : %d", pos.x);
	
	//�����X�^�[���v���C���[����������A�v���C���[��ǐ�
	if ( ( pos.x - playerpos.x <= 100 )
		&& ( pos.z - playerpos.z <= 100 ) ) {




		//�v���C���[�ɁA�ǐՁB
		//�G�́A1.5	�{�����ǐՂ��Ă���B
		pos.x = pos.x - 1.5 * (playerpos.x)/fabs(playerpos.x);
		pos.z = pos.z - 1.5 * (playerpos.z) / fabs(playerpos.z);
	}

}

//���̃Z�b�g�A�b�v
void Monster::infoSetup(float steptime, VECTOR playerpos ) {

	int		i;

	//�X�e�[�W�p�R���W�����R�c���f���̃n���h�����擾
	StageCollModel = mStage->GetCollisionModelHandle();

	//�X�e�[�W�I�u�W�F�N�g�̐����擾����
	StageObjectNum = mStage->GetObjectNum();

	// �v���C���[�����邩�ǂ����ŏ����𕪊�
	if ( mPlayer == NULL)
	{
		// �v���C���[�����Ȃ��ꍇ�́w�v���C���[�����������ǂ����x�Ȃǂ̏�������������
		PlayerNoticeDistanceCounter = 0.0f;
		PlayerNoticeDistanceCounter_XZ = 0.0f;
		SeePlayer = false;
		SeePlayerCounter = 0.0f;
		NoticePlayer = false;
		NoticePlayer_AttackMode = false;
	}
	else {
		//�G����v���C���[�ւ̃x�N�g�����Z�o
		EnemyToPlayerVec = VSub(playerpos, pos);
		EnemyToPlayerVec_XZ = VSub(VGet(playerpos.x, 0.0f, mPlayer->pos.z),
			VGet(pos.x, 0.0f, pos.z));

		//�G����v���C���[�ւ̐��K���x�N�g�����Z�o
		PlayerDirection = VNorm(EnemyToPlayerVec);
		PlayerDirection_XZ = VNorm(EnemyToPlayerVec_XZ);

		//�G����v���C���[�܂ł̋������Z�o
		PlayerDistance = VSize(EnemyToPlayerVec);
		PlayerDistance_XZ = VSize(EnemyToPlayerVec_XZ);



		//�v���C���[�ɋC�t�������ɋ���ꍇ�̓v���C���[��
		//�C�Â������ɂȂ��Ă���̎��Ԃ�i�߂�
		if (PlayerDistance < noticedistance) {
			PlayerNoticeDistanceCounter += steptime;
		}
		else {
			PlayerNoticeDistanceCounter = 0.0f;
		}

		//�v���C���[�ɋC�t�������ɋ���ꍇ�̓v���C���[��
		//�C�t�������ɂȂ��Ă���̎��Ԃ�i�߂�( ���������̂ݍl�� )
		if (PlayerDistance_XZ < noticedistance) {
			PlayerNoticeDistanceCounter_XZ += steptime;
		}
		else {
			PlayerNoticeDistanceCounter_XZ = 0.0f;
		}

		//�G�̎��E�͈̔͂Ƀv���C���[�����邩�𒲂ׂ�
		if (cos(SeeAngleRange) <
			VDot(FrontDirection, PlayerDirection_XZ)) {

			//�G�̎��E�͈̔͂Ƀv���C���[������ꍇ�͊ԂɎՕ������������𒲂ׂ�

			//�v���C���[�ƓG�̓��̈ʒu���擾
			PlayerHeadPosition = MV1GetFramePosition(mPlayer->playerInfo.data,
				MV1SearchFrame(mPlayer->playerInfo.data, "head"));
			HeadPosition = MV1GetFramePosition(monsterdata,
				MV1SearchFrame(monsterdata, "head"));

			//���݂��̓����̊ԂɎՂ���̂����邩�ǂ����𒲂ׂ�
			CollPoly = MV1CollCheck_Line(StageCollModel, -1, HeadPosition,
				PlayerHeadPosition);
			if (CollPoly.HitFlag == FALSE) {

				/*for (i = 0; i < StageObjectNum; i++)
				{
					ObjectCollModel = mStage->GetObjectCollisionModelHandle(i);

					if (ObjectCollModel == -1)
					{
						continue;
					}

					CollPoly = MV1CollCheck_Line(ObjectCollModel, -1, HeadPosition,
						PlayerHeadPosition);

					if (CollPoly.HitFlag)
					{
						break;
					}
				}*/
			}

			//�����ꍇ�͓G����v���C���[��������Ƃ�������
			SeePlayer = CollPoly.HitFlag == FALSE;
		}
		else
		{
			SeePlayer = false;
		}
		//�G����v���C���[�������Ă���ꍇ�͌�����悤�ɂȂ��Ă���̎��Ԃ�i�߂�
		if (SeePlayer)
		{
			SeePlayerCounter += steptime;
		}
		else
		{
			SeePlayerCounter = 0.0f;
		}

		//�U�����[�h�ł͂Ȃ��ꍇ�Ƀv���C���[�̑��݂ɋC�t�������������Ă��邩���`�F�b�N
		if ((SeePlayerCounter > NoticeTime_See &&
			PlayerDistance_XZ < NoticeDistance_See) ||
			PlayerNoticeDistanceCounter > NoticeTime_Distance ||
			PlayerNoticeDistanceCounter_XZ > NoticeTime_Distance)
		{
			// �����Ă���ꍇ�̓v���C���[�ɋC�t���Ă��邩�ǂ����̃t���O�𗧂Ă�
			NoticePlayer = true;
		}
		else
		{
			NoticePlayer = false;
		}

		// �퓬���[�h�Ńv���C���[�̑��݂ɋC�t�������������Ă��邩���`�F�b�N
		if (SeePlayer ||
			PlayerDistance < NoticeDistance_AttackMode ||
			PlayerDistance_XZ < NoticeDistance_AttackMode) {

			// �����Ă���ꍇ�̓v���C���[�ɋC�t���Ă��邩�ǂ����̃t���O�𗧂Ă�
			NoticePlayer_AttackMode = true;
		}
		else
		{
			NoticePlayer_AttackMode = false;
		}

		// �v���C���[�����͂ɋ���Ƃ������b�Z�[�W���͂��Ă����疳������
		// �v���C���[�ɋC�t���Ă��邱�Ƃɂ���
		if (PlayerNearDistanceMessage) {
			NoticePlayer = true;
			NoticePlayer_AttackMode = true;

			// ���b�Z�[�W���͂������Ƃ������t���O��|��
			PlayerNearDistanceMessage = false;
		}

		// �e�U���^�C�v�́u�U�����s�������ɋ��邩�ǂ����v�̃t���O���X�V
		for (i = 0; i < AttackNum; i++)
		{
			AttackDistancebool =
				PlayerDistance < AttackDistance;

			AttackDistance_XZbool =
				PlayerDistance_XZ < AttackDistance;
		}
	}
}

//�����X�^�[�̏�񐄈�
/*bool Monster::step( float steptime ) {

	//�����̏��ɕK�v�ȏ��̃Z�b�g�A�b�v
	infoSetup( steptime );



}*/

// �����X�^�[���S
void Monster::dead() {

	live = false;

}
