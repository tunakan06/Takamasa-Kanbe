#include "Title.h"
#include <math.h>

//�t�H���g�T�C�Y
#define		FONT_SIZE			40

//���j���[���ڂ�Y���W
#define		MENU_X				530
#define		MENU_Y				450

//���j���[���ڂ̖��łP���ɂ����鎞��
#define		MENU_BRINK_TIME		2.0f

//�t�F�[�h�C������
#define		FADE_IN_TIME		1.0f

//�t�F�[�h�C���҂�����
#define		FADE_IN_WAIT_TIME	0.5f

//���j���[���ڂ̃t�F�[�h�C���҂�����
#define		MENU_IN_WAIT_TIME	0.2f

//���j���[���ڂ̃t�F�[�h�C������
#define		MENU_IN_TIME		0.25f

//���j���[�X�y�[�X
#define		MENU_SPACE			64

//�^�C�g������
Title::Title() {

	//�^�C�g����ʓǂݍ���
	titleBackGraphic	=	LoadGraph("Data\\2D\\TitleBack.png");

	//���S�O���t�B�b�N�ǂݍ���
	logoGraphic			=	LoadGraph("Data\\2D\\Swordbout_logo.png");

	//�^�C�g���T�E���h�f�[�^����
	titlesound = LoadSoundMem("Data\\Sound\\BGM\\BGM_title.ogg");


	//�^�C�g���Ŏg�p����t�H���g�̍쐬
	menuFont = CreateFontToHandle(NULL, FONT_SIZE, 8, DX_FONTTYPE_ANTIALIASING_8X8);

	//�^�C�g���ƃ��j���[���ڂ̕s�����x��������
	titleOpacity		=	0;
	menuOpacity			=	0;

	//�I�����ڂ̖��ŗp�J�E���^�̏�����
	menuBrinkCounter	=	0;


	//�ŏ��̑I����ԁiNew Game�j
	selectMode = SELECT_NEW;

	//�^�C�g���J�ڏ��
	titleState = FADEIN_WAIT;

}

//�f�X�g���N�^
Title::~Title() {

	delete& titleBackGraphic;
	titleBackGraphic	=	0;

	delete& logoGraphic;
	logoGraphic			=	0;

}

//���[�h�Z���N�g����
void Title::selectModeSequence( SelectMode smode ) {
	
	//���[�h�J��
	selectMode = smode;
	//�ҋ@����
	WaitTimer(180);

}

//�^�C�g����ʏo��
int	Title::Draw(

	//���ڂ����鎞��
	float StepTime

) {

	int		i;
	double	t;
	//�L�[���͕ϐ�
	int	key;

	//���j���[���ږ��ŗp�J�E���^�̎��Ԃ�i�߂�
	menuBrinkCounter += StepTime;
	if (menuBrinkCounter > MENU_BRINK_TIME) {
		menuBrinkCounter -= MENU_BRINK_TIME;
	}

	//�^�C�g����ʏo��
	//DrawGraph(0, 0, titleBackGraphic, TRUE);

	//���S��ʓ���
	//DrawGraph(-40,0, logoGraphic, TRUE);
	

		//�L�[���ׂ͂̈̏���
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		//�I����ԑJ��
		switch (titleState) {

		//�t�F�[�h�C���҂���
		case	FADEIN_WAIT:
			counter += StepTime;
			//�t�F�[�h�C���҂����Ԃ��o�߂�����t�F�[�h�C�����J�n����
			if (counter > FADE_IN_WAIT_TIME) {
				titleState = FADEIN;
				counter = 0.0f;
			}
			break;
		//�t�F�[�h�C��
		case FADEIN:
			counter += StepTime;
			if (counter > FADE_IN_TIME)
			{
				//�t�F�[�h�C�������������烁�j���[���ڃt�F�[�h�C���҂����J�n����
				titleOpacity = 255;
				titleState = MENUIN_WAIT;
				counter = 0.0f;
			}
			else
			{
				//�t�F�[�h�C�����̃^�C�g���̕s�����x���Z�o
				titleOpacity = (int)(counter * 255 / FADE_IN_TIME);
			}
			break;
		case MENUIN_WAIT:		// ���j���[���ڃt�F�[�h�C���҂���
			counter += StepTime;
			if (counter > MENU_IN_WAIT_TIME)
			{
				// �t�F�[�h�C���҂����Ԃ��o�߂����烁�j���[���ڂ̃t�F�[�h�C�����J�n����
				titleState = MENUIN;
				counter = 0.0f;
			}
			break;
		case MENUIN:			// ���j���[���ڃt�F�[�h�C����
			counter += StepTime;
			if (counter > MENU_IN_TIME)
			{
				// �t�F�[�h�C�������������獀�ڑI�����J�n����
				menuOpacity = 255;
				titleState = SELECT;
			}
			else
			{
				// �t�F�[�h�C�����̃��j���[���ڂ̕s�����x���Z�o
				menuOpacity = (int)(counter * 255 / MENU_IN_TIME);
			}
			break;
		//���ڑI��
		case SELECT:
			//�^�C�g���̕s�����x���O�ł͂Ȃ��ꍇ�̂݃^�C�g����`�悷��
			if (titleOpacity > 0)
			{
				//�^�C�g���̔w�i�̓^�C�g���̕s�����x�ɉ����ċP�x�𒲐߂���
				int Bright = titleOpacity * 160 / 255;
				SetDrawBright(Bright / 4, Bright, Bright / 2);
				DrawGraph(0, 0, titleBackGraphic, FALSE);
				SetDrawBright(255, 255, 255);

				//�A���t�@�u�����h���[�h�Ń^�C�g���̕s�����x��ݒ肵�A�^�C�g���摜��`�悷��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleOpacity);
				DrawGraph(0, 0, titleBackGraphic, TRUE);
				//���S��ʓ���
				DrawGraph(-40, 0, logoGraphic, TRUE);
			}
			//���j���[���ڂ̕s�����x���O�ł͂Ȃ��ꍇ�̂݃��j���[���ڂ�`�悷��
			if (menuOpacity > 0) {

				//�I�����Ă��鍀�ڂ̖��ł���F�̎Z�o
				t = sin(menuBrinkCounter * DX_TWO_PI_F / MENU_BRINK_TIME);
				if (t < 0.0f) t = -t;
				//�I�����Ă��鍀�ڂ̕`��F
				SelectColor = GetColor((int)(t * 128) + 127, 0, 0);

				//�ʏ�̕`��F�̒l���擾
				NormalColor = GetColor(255, 255, 255);

				//���j���[���ڂ̐������J��Ԃ�
				DrawY = MENU_Y;
				for (i = 0; i < 3; i++) {

					//���ڂ��I������Ă��邩�ǂ����ŕ`��F��ς���
					DrawColor = (selectMode == i) ? SelectColor : NormalColor;

					//���ڂ̕`��
					DrawStringToHandle(
						MENU_X, DrawY, g_TitleMenuTable[i], DrawColor, menuFont);
					// ���ڂ̕`��Y���W���P���ڕ����Ɉړ�����
					DrawY += MENU_SPACE;
				}

				switch (selectMode) {
				case	SELECT_NEW:
					//���[�h�I��
					if (key & PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_CONTINUE);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_EXIT);
					}
					//���[�h����
					if (key & PAD_INPUT_1) {
						//�j���[�Q�[���ֈڍs
						return	SELECT_NEW;
					}
					break;
				case	SELECT_CONTINUE:
					if (key & PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_EXIT);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_NEW);
					}
					if (key & PAD_INPUT_1) {
						//�Q�[���R���e�B�j���[�ֈڍs
						return SELECT_CONTINUE;
					}
					break;
				case	SELECT_EXIT:
					if (key &PAD_INPUT_DOWN) {
						selectModeSequence(SELECT_NEW);
					}
					if (key & PAD_INPUT_UP) {
						selectModeSequence(SELECT_CONTINUE);
					}
					//���[�h����
					if (key & PAD_INPUT_1) {
						//�Q�[�����I����
						return SELECT_EXIT;
					}
					break;
				}
			}
		}
	return SELECT_MODE_NONE;
}

//�^�C�g����ʌ�n��
void Title::Terminate() {

	//�^�C�g����ʂ̍폜
	DeleteGraph( titleBackGraphic );

	//���S�̍폜
	DeleteGraph( logoGraphic );

	//���j���[�t�H���g�̍폜
	DeleteFontToHandle( menuFont );

}