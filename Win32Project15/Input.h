#ifndef _INPUT_H
#define _INPUT_H

#include "DxLib.h"

//�`�F�b�N����Q�[���p�b�h�̐�
#define		MAX_GAMEPAD_NUM		16

// �L�[�{�[�h�̓��͏�Ԃ��擾���邽�߂̃o�b�t�@�̃T�C�Y
#define		KEY_STATE_BUFFER_SIZE	256

class Input {

		//���͏��
		typedef enum _EInputType
		{
			EInputType_Left,				// �������͍�
			EInputType_Right,				// �������͉E
			EInputType_Up,					// �������͏�
			EInputType_Down,				// �������͉�

			EInputType_Camera_Left,			// �J�����p�������͍�
			EInputType_Camera_Right,		// �J�����p�������͉E
			EInputType_Camera_Up,			// �J�����p�������͏�
			EInputType_Camera_Down,			// �J�����p�������͉�

			EInputType_Attack,				// �U���{�^��
			EInputType_Defence,				// �h��{�^��
			EInputType_Jump,				// �W�����v�{�^��
			EInputType_Pause,				// �|�[�Y�{�^��

			EInputType_Num,					// ���̓^�C�v�̐�
		} EInputType;
		
		//DirectInput�̓��͏��^�C�v
		typedef enum _EDInputType
		{
			EDInputType_X,					// �X�e�B�b�N�̂w��
			EDInputType_Y,					// �X�e�B�b�N�̂x��
			EDInputType_Z,					// �X�e�B�b�N�̂y��
			EDInputType_Rx,					// �X�e�B�b�N�̂w����]
			EDInputType_Ry,					// �X�e�B�b�N�̂x����]
			EDInputType_Rz,					// �X�e�B�b�N�̂y����]
			EDInputType_POV,				// �����R���g���[��
			EDInputType_Button,				// �{�^��
		} EDInputType;

		//�Q�[���ł̓��͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή����
		struct SInputTypeInfo
		{
			//�p�b�h�ԍ�
			int              PadNo;

			//DirectInput �̓��͏��^�C�v
			EDInputType      DirectInputType;

			//�T�u���( DirectInputType �ɂ���ĈӖ����ς�� )
			int              SubInfo[2];

			//�Ή�����L�[�{�[�h�̃L�[( KEY_INPUT_UP �Ȃ� )
			int              KeyInput;
		} g_InpTyInf;

		//���͏����p�̏��
		struct SInputSystemData {

			//�Q�[�����̓��͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή����
			SInputTypeInfo   InputTypeInfo[EInputType_Num];

			// DirectInput �̃p�b�h�̓��͏��
			DINPUT_JOYSTATE  DirectInputState[MAX_GAMEPAD_NUM];

			//�L�[�̓��͏��
			char             KeyInput[KEY_STATE_BUFFER_SIZE];

			//�{�^���̓��͏��
			int              ButtonInput;

			//�{�^���̉����ꂽ�u�Ԃ݂̂̓��͏��
			int              ButtonEdgeInput;

			//�J��������p�̃X�e�B�b�N���͏��
			VECTOR           CameraStickInput;

		} g_InpSys;

	public:

		Input();

		~Input();

		//���͏���
		void ProcessInput();

};

#endif
