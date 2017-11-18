#include "Weapon.h"
#include "Character.h"


// キャラクターのデータファイルが格納されているフォルダ
#define CHARADATA_DIR					"Data\\Character\\"

//素材タイプ名
static const char		*g_MaterialTypeName[EMaterialType_Num] =
{
	"grass",			// EMaterialType_Grass
	"metal",			// EMaterialType_Metal
	"soil",				// EMaterialType_Soil
	"stone",			// EMaterialType_Stone
	"wood",				// EMaterialType_Wood
};

Weapon::Weapon(){

	mTextParam	= new TextParam();
	mSound = new Sound();
	mPlayer = new Player();

	TextParam::STextParamInfo	CommonTextParam;
	TextParam::STextParamInfo	TextParam;
	SCharaWeaponBaseInfo		*WBInfo;
	char						String[256];
	int							i;
	int							j;
	const char					*DirectoryName;
	const char					*ParamString;

	//各武器のファイルが格納されているフォルダ名が記述されているテキストファイルを読み込む
	mTextParam->LoadTextParam(&CommonTextParam, CHARADATA_DIR "Weapon\\Param.txt");

	//武器の数だけ繰り返し
	WBInfo = sCharaWeaponBaseInfo;
	for (i = 0; i < ECharaWeapon_Num; i++, WBInfo++) {

		//武器のファイルが格納されているフォルダ名を取得する
		DirectoryName = mTextParam->GetTextParamString(&CommonTextParam, "CharaWeapon%03d_DirectoryName", i);
		strcpy_s(WBInfo->DirectoryName, _countof(WBInfo->DirectoryName), DirectoryName);

		//武器のパラメータが記述されたテキストファイルを読み込む
		mTextParam->LoadTextParam(&TextParam, CHARADATA_DIR "Weapon\\%s\\Param.txt", WBInfo->DirectoryName);

		//武器の名前を取得する
		ParamString = mTextParam->GetTextParamString(&TextParam, "Name");
		strcpy_s(WBInfo->Name, _countof(WBInfo->DirectoryName), ParamString);

		//3Dファイルモデル名を取得
		ParamString = mTextParam->GetTextParamString(&TextParam, "ModelPath");
		if (ParamString == NULL) {
			WBInfo->ModelHandle = -1;
		}
		else {
			//3Dモデルファイルを読み込み
			sprintf_s(String, CHARADATA_DIR "Weapon\\%s\\%s", WBInfo->DirectoryName, ParamString);
			WBInfo->ModelHandle = MV1LoadModel(String);
			if (WBInfo->ModelHandle == -1) {
				return;
			}
		}

		//武器が何かに衝突したときに鳴らす共通の音の登録
		sprintf_s(String, "SE\\Weapon\\%s\\MAT_impact_com", WBInfo->DirectoryName);
		WBInfo->MaterialCommonSound = mSound->AddSound(String, true);

		//武器が各素材に衝突したときに鳴らす音の登録
		for (j = 0; j < EMaterialType_Num; j++)
		{
			sprintf_s(String, "SE\\Weapon\\%s\\MAT_impact_%s", WBInfo->DirectoryName, g_MaterialTypeName[i]);
			WBInfo->MaterialSound[j] = mSound->AddSound(String, true);
		}
	}

	weaponstring = "Sabel";

	if (weaponstring == NULL) {



	}
	else {




	}

	weapondata = MV1LoadModel("Data\\Character\\Player\\Sabel.mv1");

	sayadata = MV1LoadModel("Data\\Character\\Player\\Saya.mv1");

	model = mPlayer->playerInfo.data;
	
	righthandframeNo = MV1SearchFrame(model, "wp");

	//weaponflm = MV1SearchFrame(gPlayer->playerInfo.data, "sayabone");
	//MV1SetFrameUserLocalMatrix( gPlayer->playerInfo.data, weaponflm , MGetIdent());

}

Weapon::~Weapon(){}

//武器出力
void Weapon::Draw() {

	//DrawString(800, 450,"MV1SF" ,GetColor(255, 255, 255) );
	//DrawFormatString(1000, 650, GetColor(100, 100, 100), "MV1SF:%d", righthandframeNo);
	//MV1DetachAnim(gPlayer->playerInfo.data, );

	//武器設定
	wd = weapondata;

	//キャラクターモデルの右手フレームの行列を取得
	righthandmatrix = MV1GetFrameLocalWorldMatrix( model, righthandframeNo);
	// キャラクターモデルの右手フレームの行列をアクセサリモデルの行列としてセットしてから描画
	MV1SetMatrix(wd, righthandmatrix);
	//武器３Ｄモデルを描画
	MV1DrawModel(wd);


}

