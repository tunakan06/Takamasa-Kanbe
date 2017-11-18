#include "GameFrame.h"

#define		MAX_DELTA_TIME		1.0/120.0f
#define		MAX_FRAME_NUM		8
#define		GAME_SCREEN_WIDTH	1200
#define		GAME_SCREEN_HEIGHT	720

// ���L���ʉ��̃t�@�C����
static const char *g_CommonSEFileName[ECommonSE_Num] =
{
	"system_alert.wav",
	"system_cancel.wav",
	"system_counter.wav",
	"system_cursor.wav",
	"system_enter.wav",
};

GameFrame::GameFrame() {


}

GameFrame::~GameFrame() {



}

//���C���̏���
void	GameFrame::Main( ){

	Task::STaskInfo TInfo = TGData.Info;

	//����������
	Initialize();

	//���C�����[�v
	MainLoop( TInfo );

	//��n������
	Terminate();

}

//����������
void	GameFrame::Initialize() {

	int		i;
	char	FilePath[ MAX_PATH ];

	//�E�B���h�E���[�h�ŋN�����邩�m�F
	if ( MessageBox( NULL, "�E�B���h�E���[�h�ŋN�����܂����H", "��ʃ��[�h�m�F", MB_YESNO ) == IDYES ) {
		
		ChangeWindowMode(TRUE);

	}

	//�ᕉ�׏������[�h�ŋN�����邩�m�F
	if (MessageBox(NULL, "�ᕉ�׏������[�h�ŋN�����܂����H", "�������׃��[�h�m�F", MB_YESNO) == IDYES) {

		s_GameFrameInfo.LowSpecMode = true;
	
	}

	//�Q�[����ʉ𑜓x�ݒ�
	SetGraphMode( GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);

	//�E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("Sword Bout");

	//�ᕉ�׏������[�h���ǂ�����XAudio���g�p���邩�ǂ����̐ݒ�ύX
	SetEnableXAudioFlag( s_GameFrameInfo.LowSpecMode ? FALSE : TRUE );

	//3D�T�E���h��1���[�g��������̒l���Z�b�g
	Set3DSoundOneMetre( 100.0f );

	DrawStringToHandle(1000, 650, "Now Loading...", GetColor(100, 100, 100), s_GameFrameInfo.FontHandle[EFontHandle_Small]);

	//DX���C�u��������������
	DxLib_Init();

	//�t�H���g�n���h���̍쐬
	s_GameFrameInfo.FontHandle[EFontHandle_Small] = CreateFontToHandle(NULL, 24, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	s_GameFrameInfo.FontHandle[EFontHandle_Midium] = CreateFontToHandle(NULL, 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	s_GameFrameInfo.FontHandle[EFontHandle_Big] = CreateFontToHandle(NULL, 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);

	//���L���ʉ��̓ǂݍ���
	for (i = 0; i < ECommonSE_Num ; i++ ) {
		sprintf_s( FilePath, "Data\\Sound\\SE\\Common\\%s", g_CommonSEFileName[ i ] );
		s_GameFrameInfo.CommonSEHandle[i] = LoadSoundMem( FilePath );

	}

	DrawStringToHandle(1000,650,"Now Loading...", GetColor(100,100,100), s_GameFrameInfo.FontHandle[EFontHandle_Small]);

	//�^�C�g������
	mTitle = new Title();

	//�T�E���h����
	mSound = new Sound();

	//�e�L�X�g�p�����[�^����
	//mTextParam = new TextParam();

	//�悸�̓^�C�g����ʂ��o��
	gameMode = GAME_TITLE;

	//�Q�[�����C������
	mGameMain = new GameMain();

	s_GameFrameInfo.backDispFrameTime = GetNowHiPerformanceCount();
	s_GameFrameInfo.frameCounter = 0;
	s_GameFrameInfo.dispFrameCount = 0;

}

//���C�����[�v
void	GameFrame::MainLoop( Task::STaskInfo		TInfo ) {
	
	LONGLONG			NowTime;

	//�`���͗����
	SetDrawScreen( DX_SCREEN_BACK );

	//�ŏ��̃t���[���̏�Ԑ��ڎ��ԂȂǂ��Z�b�g
	s_GameFrameInfo.stepTime = MAX_DELTA_TIME;
	s_GameFrameInfo.prevTime = GetNowHiPerformanceCount();
	s_GameFrameInfo.stepNum = 1;

	//�^�C�g���~���[�W�b�N�Đ�
	mSound->Output(0);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		switch (gameMode) {
		case GAME_TITLE:
			//�^�C�g����ʏo��
			if (mTitle->Draw(s_GameFrameInfo.stepTime ) == Title::SELECT_NEW) {//z�L�[�ŃQ�[�����C����

				//�^�C�g���T�E���h��~
				mSound->stopSound( 0 );

				//�T�E���h�o��
				mSound->Output(1);

				//�^�C�g���̌�n��
				mTitle->Terminate();

				//�Q�[���̃��C����
				gameMode = GAME_MAIN;
			}
			else if (mTitle->Draw(s_GameFrameInfo.stepTime ) == Title::SELECT_EXIT) {

				//�Q�[���I����
				gameMode = GAME_EXIT;
			}
			break;
		case GAME_MAIN:
			//�Q�[�����C���o��
			mGameMain->Draw( &TInfo ,s_GameFrameInfo.stepTime );
			break;
		case GAME_EXIT:

			Terminate();
			break;
		default:
			break;
		}
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		//���݂̎��Ԃ��擾
		NowTime  = GetNowHiPerformanceCount();

		//�O��擾�������Ԃ���̌o�ߎ��Ԃ��Z�o
		s_GameFrameInfo.stepTime = ( NowTime - s_GameFrameInfo.prevTime) / 1000000.0f;

		//��Ԑ��ڏ������s���񐔂��Z�o
		s_GameFrameInfo.stepNum = (int)(s_GameFrameInfo.stepTime / MAX_DELTA_TIME );

		//��Ԑ��ڏ������s���񐔂��O��̏ꍇ�͂P��ɂ���
		if (s_GameFrameInfo.stepNum == 0)
		{
			s_GameFrameInfo.stepNum = 1;
		}

		else
		{
			//�O��ł͂Ȃ��ꍇ�͏�Ԑ��ڂŐi�߂鎞�Ԃ���Ԑ��ڂ��s���񐔂Ŋ���
			s_GameFrameInfo.stepTime /= s_GameFrameInfo.stepNum;

			//������Ԑ��ڂ��s���񐔂��ő�l�𒴂��Ă�����ő�l�ɗ}����
			if (s_GameFrameInfo.stepNum > MAX_FRAME_NUM)
			{
				s_GameFrameInfo.stepNum = MAX_FRAME_NUM;
			}
		}

		//����̎��Ԃ�ۑ�����
		s_GameFrameInfo.prevTime = NowTime;

		//�t���[�����[�g�v���p�̃J�E���^���P����
		s_GameFrameInfo.frameCounter++;

		//�O��t���[�����[�g���X�V���Ă���P�b�o�߂�����\���p�t���[���J�E���g���X�V����
		if ( NowTime - s_GameFrameInfo.backDispFrameTime > 1000000)
		{
			//�\���p�t���[���J�E���g���X�V
			s_GameFrameInfo.dispFrameCount = s_GameFrameInfo.frameCounter;

			//�v���p�t���[���J�E���^��������
			s_GameFrameInfo.frameCounter = 0;

			//�\���p�t���[���J�E���g���X�V�������Ԃ��X�V
			s_GameFrameInfo.backDispFrameTime = NowTime;
		}

		// ��ʂ�����������
		ClearDrawScreen();
	}

}

//��n������
void	GameFrame::Terminate() {

	//DX���C�u�����I������
	DxLib_End();

}