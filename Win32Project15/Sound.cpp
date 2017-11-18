#include "Sound.h"

//３Ｄサウンドのデフォルトの音が聞こえる範囲
#define DEFAULT_RADIUS			5000.0f

// サウンドのデフォルト同時再生可能数
#define DEFAULT_BUFFER_NUM		(6)

// 登録できるサウンドの最大数
#define MAX_SOUNDINFO_NUM		1024

//サウンドファイルが存在するフォルダパス
#define FILE_DIRECTORY_PATH		"Data\\Sound\\"

//サウンドファイルの拡張子
#define FILE_EXENAME			"wav"

Sound::Sound() {

	//mTextParam = new TextParam();

	sounddata[0] = LoadSoundMem("Data\\Sound\\BGM\\BGM_title.ogg");
	sounddata[1] = LoadSoundMem("Data\\Sound\\BGM\\BGM_stg0.ogg");
	sounddata[2] = LoadSoundMem("Data\\Sound\\BGM\\BGM_stg1.ogg");
}


Sound::~Sound() {}

//サウンド出力関数
void Sound::Output( int i ) {

	//SetLoopSamplePosSoundMem(loopstartposition, sounddata[0]);
	//SetLoopStartSamplePosSoundMem(loopendposition, sounddata[0]);

	//サウンド再生
	PlaySoundMem(sounddata[i], DX_PLAYTYPE_LOOP );

}

//サウンド停止関数
void Sound::stopSound( int i ) {

	//タイトルサウンド停止
	StopSoundMem(sounddata[i]);

}

//サウンドファイルを追加する
int Sound::AddSound(
	//追加するサウンドファイルのパス
	const char* FilePath,
	// ３Ｄで鳴らすサウンドかどうか( true:3Dサウンド  false:2Dサウンド )
	bool Is3DSound
){

	int			i;
	int			Index;
	SSoundInfo	*Info;
	char        FilePath2[MAX_PATH];
	TextParam::STextParamInfo  TextParam;
	float       Radius;
	int         Volume;

	//既に登録してあるサウンドの中に、登録しようとしているサウンドが存在するか調べる
	Info = sSoundSystemData.Sound;
	for (Index = 0; Index < sSoundSystemData.SoundNum; Index++, Info++) {
		if((Info->Is3DSound == Is3DSound) && ( strcmp( Info->FilePath, FilePath ) == 0) ) {
			// 存在した場合は、既に登録済みのサウンドの登録番号を返す
			return Index;
		}
	}

	//登録しているサウンドの数が最大数に達していたらエラー
	if (sSoundSystemData.SoundNum == MAX_SOUNDINFO_NUM)
	{
		return -1;
	}

	//３Ｄサウンドかどうかを保存
	Info->Is3DSound = Is3DSound;

	//作成するサウンドが３Ｄサウンドかどうかを設定する
	SetCreate3DSoundFlag(Is3DSound);

	// ３Ｄサウンドの場合は聞こえる距離や音量をテキストファイルから読み取る
	if (Info->Is3DSound)
	{
		Radius = DEFAULT_RADIUS;
		Volume = 255;
		mTextParam->LoadTextParam(&TextParam, "%s%s_Param.txt", FILE_DIRECTORY_PATH, FilePath);
		Radius = mTextParam->GetTextParamFloat(&TextParam, "Radius");
		Volume = (int)(mTextParam->GetTextParamFloat(&TextParam, "Volume") * 255.0f);
	}

	// サウンドファイルを読み込む
	Info->HandleNum = 0;
	for (i = 0; i < MAX_HANDLE_NUM; i++)
	{
		// サウンドファイルパスの作成
		sprintf_s(FilePath2, "%s%s_%02d.%s",
			FILE_DIRECTORY_PATH, FilePath, i, FILE_EXENAME);

		// サウンドファイルが無かったらループを抜ける
		if (FileRead_size(FilePath2) < 0)
		{
			break;
		}

		// サウンドファイルの読み込み
		Info->Handle[i] = LoadSoundMem(FilePath2, DEFAULT_BUFFER_NUM);
		if (Info->Handle[i] == -1)
		{
			return -1;
		}

		// サウンドファイルの場合は聞こえる距離と音量をサウンドハンドルに設定する
		if (Info->Is3DSound)
		{
			Set3DRadiusSoundMem(Radius, Info->Handle[i]);
			ChangeVolumeSoundMem(Volume, Info->Handle[i]);
		}
	}

	// サウンドハンドルの数を保存
	Info->HandleNum = i;

	// 一つも読み込めなかった場合はエラー
	if (Info->HandleNum == 0)
	{
		return -1;
	}

	// ファイルパスを保存
	strcpy_s(Info->FilePath, _countof(Info->FilePath), FilePath);

	// サウンドの数を増やす
	sSoundSystemData.SoundNum++;

	// サウンドの登録番号を返す
	return Index;

}