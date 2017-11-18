#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

#include "Title.h"
#include "Sound.h"
#include "DxLib.h"
#include "TextParam.h"
#include "GameMain.h"

// ���L���ʉ�
typedef enum _ECommonSE
{
	ECommonSE_Alert,		// �x��
	ECommonSE_Cancel,		// �L�����Z��
	ECommonSE_Counter,		// �J�E���g
	ECommonSE_Cursor,		// �J�[�\��
	ECommonSE_Enter,		// ����

	ECommonSE_Num,			// ���L���ʉ��̐�
} ECommonSE;

class GameFrame {

private:

	//�Q�[�����[�h�̏��
	enum GameMode {

		GAME_TITLE,
		GAME_MAIN,
		GAME_EXIT,

		GAME_MODE_NUM,
	} gameMode;


	//�t�H���g�n���h���̎��
	enum font {

		EFontHandle_Small,
		EFontHandle_Midium,
		EFontHandle_Big,

		EFontHandle_Num,
	};



	Title*		mTitle;
	GameMain*	mGameMain;

	struct SGameFrameInfo{

		//�Ꮘ�����׃��[�h�ϐ�
		bool LowSpecMode;

		//�t�H���g�n���h���ϐ�
		int	FontHandle[EFontHandle_Num];

		// ���L���ʉ��̃n���h��
		int	CommonSEHandle[ECommonSE_Num];

		//��Ԑ��ڎ��ԂȂ�
		double		stepTime;
		LONGLONG	prevTime;
		int			stepNum;

		// �t���[�����[�g�v���p�̕ϐ��̏�����
		LONGLONG backDispFrameTime;
		int frameCounter;
		int dispFrameCount;

	} s_GameFrameInfo;




public:

	typedef struct _STask_GameFrameData{

		Task::STaskInfo			Info;

	} STask_GameFrameData;

	STask_GameFrameData		TGData;

	TextParam*	mTextParam;
	Sound*		mSound;

	GameFrame();

	~GameFrame();

	//���C���̏���
	void	Main();

	//����������
	void	Initialize();

	//���C�����[�v
	void	MainLoop( Task::STaskInfo		TInfo );

	//��n������
	void	Terminate();

};

#endif
