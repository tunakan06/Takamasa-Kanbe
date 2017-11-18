#ifndef _TITLE_H
#define _TITLE_H

#include "DxLib.h"
#include "Sound.h"

static const char *g_TitleMenuTable[] =
{
	"GAME START",
	"CONTINUE GAME",
	"EXIT" };

class Title{

public:

	//�^�C�g������
	Title();

	//�f�X�g���N�^
	~Title();

	//�I�����[�h�̑J�ڏ��
	enum TitleState {

		FADEIN_WAIT,
		FADEIN,
		MENUIN_WAIT,
		MENUIN,
		SELECT,

		TITLE_STATE_NUM,

	};

	//���肵���I�����[�h
	enum SelectMode {

		SELECT_NEW,
		SELECT_CONTINUE,
		SELECT_EXIT,

		SELECT_MODE_NONE,

		SELECT_MODE_NUM,

	};

	//�^�C�g���̏����̏��
	TitleState	titleState;

	//���肵���I�����[�h
	SelectMode	selectMode;

	//�^�C�g����ʏo��
	int Draw( float StepTime );

	//�^�C�g����ʌ�n��
	void Terminate();

private:

	Sound* tSound;

	//�^�C�g����ʂŎg�p����t�H���g�̍쐬
	int menuFont;

	//�^�C�g����ʊi�[�ϐ�
	int titleBackGraphic;

	//���S��ʊi�[�ϐ�
	int logoGraphic;

	//�T�E���h�i�[�ϐ�
	int titlesound;

	//���j���[���ڂ�Y���W
	int DrawY;

	//�`��F
	int DrawColor;

	//�I�����[�h�Ƃ���ȊO�̂̕\���F
	int SelectColor;
	int NormalColor;

	//�^�C�g���ƃ��j���[���ڂ̕s�����x
	int titleOpacity;
	int menuOpacity;

	//�ėp�J�E���^
	float counter;

	//�I�����ڂ̖��ŗp�J�E���^
	float menuBrinkCounter;

	//���[�h�Z���N�g����
	void selectModeSequence( SelectMode smode );


};

#endif
