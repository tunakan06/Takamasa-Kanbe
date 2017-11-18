#ifndef _STAGE_H
#define _STAGE_H

#include "DxLib.h"

#include "BinaryFile.h"

// �X�e�[�W�f�[�^�Ɋ܂߂���ő�L������
#define STAGE_CHARA_MAX_NUM							(256)

// �X�e�[�W�f�[�^�Ɋ܂߂���ő�I�u�W�F�N�g��
#define STAGE_OBJECT_MAX_NUM						(512)

// �X�e�[�W�f�[�^�Ɋ܂߂���ő�I�u�W�F�N�g�p���f����
#define STAGE_OBJECT_MODEL_MAX_NUM					(256)

// �X�e�[�W�f�[�^�Ɋ܂߂���ő�C�x���g��
#define STAGE_EVENT_MAX_NUM							(256)

// ��̃C�x���g�ӂ�Ɏw��ł���I�u�W�F�N�g�̍ő吔
#define STAGE_EVENT_OBJECT_MAX_NUM					(16)

// �R���W�������f���̍ő�}�e���A����
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

class Stage {

	//�R���W�����p�R�c���f���n���h��
	int CollisionModelHandle;

	BinaryFile*	mBinaryFile;

	//�f�[�^�E�|�W�V�����i�[�ϐ�
	int			stagedata;
	int			stagedata_sky;
	int			stagedata_c;

	int			ObjectInfoNum;
	int			ObjectCollisionModelHandle[STAGE_OBJECT_MAX_NUM];

	bool		Load;
	int			ModelHandle;

public:

	//�X�e�[�W�̃R���W�����p�R�c���f���n���h��
	int GetCollisionModelHandle();

	//�X�e�[�W�I�u�W�F�N�g�̐�
	int	GetObjectNum();

	//�I�u�W�F�N�g���g�p����R���W�����p�R�c���f���n���h��
	int	GetObjectCollisionModelHandle(int Index);

	//�I�u�W�F�N�g���f���̓ǂݍ���
	void	ObjectModel_Load( int Index );

	Stage();

	~Stage();

	//�X�e�[�W�Z�b�g�A�b�v
	void	Setup();

	//�X�e�[�W�f�[�^�o��
	int	Draw();

	//�p�x�����֐�
	//float ctArg();

};

#endif
