#include "Weapon.h"
#include "Character.h"


// �L�����N�^�[�̃f�[�^�t�@�C�����i�[����Ă���t�H���_
#define CHARADATA_DIR					"Data\\Character\\"

//�f�ރ^�C�v��
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

	//�e����̃t�@�C�����i�[����Ă���t�H���_�����L�q����Ă���e�L�X�g�t�@�C����ǂݍ���
	mTextParam->LoadTextParam(&CommonTextParam, CHARADATA_DIR "Weapon\\Param.txt");

	//����̐������J��Ԃ�
	WBInfo = sCharaWeaponBaseInfo;
	for (i = 0; i < ECharaWeapon_Num; i++, WBInfo++) {

		//����̃t�@�C�����i�[����Ă���t�H���_�����擾����
		DirectoryName = mTextParam->GetTextParamString(&CommonTextParam, "CharaWeapon%03d_DirectoryName", i);
		strcpy_s(WBInfo->DirectoryName, _countof(WBInfo->DirectoryName), DirectoryName);

		//����̃p�����[�^���L�q���ꂽ�e�L�X�g�t�@�C����ǂݍ���
		mTextParam->LoadTextParam(&TextParam, CHARADATA_DIR "Weapon\\%s\\Param.txt", WBInfo->DirectoryName);

		//����̖��O���擾����
		ParamString = mTextParam->GetTextParamString(&TextParam, "Name");
		strcpy_s(WBInfo->Name, _countof(WBInfo->DirectoryName), ParamString);

		//3D�t�@�C�����f�������擾
		ParamString = mTextParam->GetTextParamString(&TextParam, "ModelPath");
		if (ParamString == NULL) {
			WBInfo->ModelHandle = -1;
		}
		else {
			//3D���f���t�@�C����ǂݍ���
			sprintf_s(String, CHARADATA_DIR "Weapon\\%s\\%s", WBInfo->DirectoryName, ParamString);
			WBInfo->ModelHandle = MV1LoadModel(String);
			if (WBInfo->ModelHandle == -1) {
				return;
			}
		}

		//���킪�����ɏՓ˂����Ƃ��ɖ炷���ʂ̉��̓o�^
		sprintf_s(String, "SE\\Weapon\\%s\\MAT_impact_com", WBInfo->DirectoryName);
		WBInfo->MaterialCommonSound = mSound->AddSound(String, true);

		//���킪�e�f�ނɏՓ˂����Ƃ��ɖ炷���̓o�^
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

//����o��
void Weapon::Draw() {

	//DrawString(800, 450,"MV1SF" ,GetColor(255, 255, 255) );
	//DrawFormatString(1000, 650, GetColor(100, 100, 100), "MV1SF:%d", righthandframeNo);
	//MV1DetachAnim(gPlayer->playerInfo.data, );

	//����ݒ�
	wd = weapondata;

	//�L�����N�^�[���f���̉E��t���[���̍s����擾
	righthandmatrix = MV1GetFrameLocalWorldMatrix( model, righthandframeNo);
	// �L�����N�^�[���f���̉E��t���[���̍s����A�N�Z�T�����f���̍s��Ƃ��ăZ�b�g���Ă���`��
	MV1SetMatrix(wd, righthandmatrix);
	//����R�c���f����`��
	MV1DrawModel(wd);


}

