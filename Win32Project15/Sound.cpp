#include "Sound.h"

//�R�c�T�E���h�̃f�t�H���g�̉�����������͈�
#define DEFAULT_RADIUS			5000.0f

// �T�E���h�̃f�t�H���g�����Đ��\��
#define DEFAULT_BUFFER_NUM		(6)

// �o�^�ł���T�E���h�̍ő吔
#define MAX_SOUNDINFO_NUM		1024

//�T�E���h�t�@�C�������݂���t�H���_�p�X
#define FILE_DIRECTORY_PATH		"Data\\Sound\\"

//�T�E���h�t�@�C���̊g���q
#define FILE_EXENAME			"wav"

Sound::Sound() {

	//mTextParam = new TextParam();

	sounddata[0] = LoadSoundMem("Data\\Sound\\BGM\\BGM_title.ogg");
	sounddata[1] = LoadSoundMem("Data\\Sound\\BGM\\BGM_stg0.ogg");
	sounddata[2] = LoadSoundMem("Data\\Sound\\BGM\\BGM_stg1.ogg");
}


Sound::~Sound() {}

//�T�E���h�o�͊֐�
void Sound::Output( int i ) {

	//SetLoopSamplePosSoundMem(loopstartposition, sounddata[0]);
	//SetLoopStartSamplePosSoundMem(loopendposition, sounddata[0]);

	//�T�E���h�Đ�
	PlaySoundMem(sounddata[i], DX_PLAYTYPE_LOOP );

}

//�T�E���h��~�֐�
void Sound::stopSound( int i ) {

	//�^�C�g���T�E���h��~
	StopSoundMem(sounddata[i]);

}

//�T�E���h�t�@�C����ǉ�����
int Sound::AddSound(
	//�ǉ�����T�E���h�t�@�C���̃p�X
	const char* FilePath,
	// �R�c�Ŗ炷�T�E���h���ǂ���( true:3D�T�E���h  false:2D�T�E���h )
	bool Is3DSound
){

	int			i;
	int			Index;
	SSoundInfo	*Info;
	char        FilePath2[MAX_PATH];
	TextParam::STextParamInfo  TextParam;
	float       Radius;
	int         Volume;

	//���ɓo�^���Ă���T�E���h�̒��ɁA�o�^���悤�Ƃ��Ă���T�E���h�����݂��邩���ׂ�
	Info = sSoundSystemData.Sound;
	for (Index = 0; Index < sSoundSystemData.SoundNum; Index++, Info++) {
		if((Info->Is3DSound == Is3DSound) && ( strcmp( Info->FilePath, FilePath ) == 0) ) {
			// ���݂����ꍇ�́A���ɓo�^�ς݂̃T�E���h�̓o�^�ԍ���Ԃ�
			return Index;
		}
	}

	//�o�^���Ă���T�E���h�̐����ő吔�ɒB���Ă�����G���[
	if (sSoundSystemData.SoundNum == MAX_SOUNDINFO_NUM)
	{
		return -1;
	}

	//�R�c�T�E���h���ǂ�����ۑ�
	Info->Is3DSound = Is3DSound;

	//�쐬����T�E���h���R�c�T�E���h���ǂ�����ݒ肷��
	SetCreate3DSoundFlag(Is3DSound);

	// �R�c�T�E���h�̏ꍇ�͕������鋗���≹�ʂ��e�L�X�g�t�@�C������ǂݎ��
	if (Info->Is3DSound)
	{
		Radius = DEFAULT_RADIUS;
		Volume = 255;
		mTextParam->LoadTextParam(&TextParam, "%s%s_Param.txt", FILE_DIRECTORY_PATH, FilePath);
		Radius = mTextParam->GetTextParamFloat(&TextParam, "Radius");
		Volume = (int)(mTextParam->GetTextParamFloat(&TextParam, "Volume") * 255.0f);
	}

	// �T�E���h�t�@�C����ǂݍ���
	Info->HandleNum = 0;
	for (i = 0; i < MAX_HANDLE_NUM; i++)
	{
		// �T�E���h�t�@�C���p�X�̍쐬
		sprintf_s(FilePath2, "%s%s_%02d.%s",
			FILE_DIRECTORY_PATH, FilePath, i, FILE_EXENAME);

		// �T�E���h�t�@�C�������������烋�[�v�𔲂���
		if (FileRead_size(FilePath2) < 0)
		{
			break;
		}

		// �T�E���h�t�@�C���̓ǂݍ���
		Info->Handle[i] = LoadSoundMem(FilePath2, DEFAULT_BUFFER_NUM);
		if (Info->Handle[i] == -1)
		{
			return -1;
		}

		// �T�E���h�t�@�C���̏ꍇ�͕������鋗���Ɖ��ʂ��T�E���h�n���h���ɐݒ肷��
		if (Info->Is3DSound)
		{
			Set3DRadiusSoundMem(Radius, Info->Handle[i]);
			ChangeVolumeSoundMem(Volume, Info->Handle[i]);
		}
	}

	// �T�E���h�n���h���̐���ۑ�
	Info->HandleNum = i;

	// ����ǂݍ��߂Ȃ������ꍇ�̓G���[
	if (Info->HandleNum == 0)
	{
		return -1;
	}

	// �t�@�C���p�X��ۑ�
	strcpy_s(Info->FilePath, _countof(Info->FilePath), FilePath);

	// �T�E���h�̐��𑝂₷
	sSoundSystemData.SoundNum++;

	// �T�E���h�̓o�^�ԍ���Ԃ�
	return Index;

}