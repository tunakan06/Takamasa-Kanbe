#include "TextParam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

TextParam::TextParam(){}

TextParam::~TextParam(){}

// �p�����[�^���擾����֐��̐擪�ŕK���s����^����
// �ό�������p�����[�^���𐶐����āA�z�񒆂̃p�����[�^�̃C���f�b�N�X���擾����
#define GETTEXTPARAM_COMMON		\
	int Index;\
	va_list VaList;\
	char ParamNameS[ MAX_PATH ];\
	\
	va_start( VaList, ParamName );\
	vsprintf_s( ParamNameS, ParamName, VaList );\
	va_end( VaList );\
	\
	Index = SearchTextParam( TxtParam, ParamNameS );

// �p�����[�^�^�C�v��
static const char *g_TextParamTypeName[ETextParamType_Num] =
{
	"int",
	"bool",
	"float",
	"vector",
	"string",
	"color"
};

//�p�����[�^�t�@�C����ǂݍ���
bool	TextParam::LoadTextParam(
	// �e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,
	// �t�@�C���p�X
	const char *FilePath,
	// �t�@�C���p�X�����p�ό���
	...){

	FILE   *fp;
	errno_t error;
	char    Type[64];
	char    Name[TEXTPARAM_NAME_MAXLENGTH];
	char    Param1[64];
	char    Param2[64];
	char    Param3[64];
	char    Param4[64];
	va_list VaList;
	char	FilePathS[ MAX_PATH ];
	int     i;
	int     Num;

	//�t�@�C���p�X����
	va_start(VaList, FilePath);
	vsprintf_s(FilePathS, FilePath,VaList);
	va_end(VaList);

	//�e�L�X�g�^�C�v�̓ǂݍ��ݎw��Ńt�@�C�����J��
	error = fopen_s(&fp, FilePathS,"rt");
	//�t�@�C�����J�����ƂɎ��s�����玸�s�I��
	if (fp == NULL)
	{
		return false;
	}

	//�e�L�X�g�p�����[�^�\���̂��O�ŏ���������
	memset(TxtParam, 0, sizeof(STextParamInfo));

	// �e�L�X�g�t�@�C���̏I�[�ɓ��B����܂Ń��[�v
	Num = 0;
	while (fscanf_s(fp, "%s %s = %s", Type, sizeof(Type), Name, sizeof(Name), Param1, sizeof(Param1)) != EOF){
		// �p�����[�^�̖��O��ۑ�
		strcpy_s(TxtParam->Param[Num].Name, _countof(TxtParam->Param[Num].Name), Name);
		// �p�����[�^�̃^�C�v�𒲂ׂ�
		for (i = 0; i < ETextParamType_Num; i++)
		{
			if (strcmp(g_TextParamTypeName[i], Type) == 0)
			{
				break;
			}
		}
		//�^�C�v�������������ꍇ�̂ݏ���
		if (i == ETextParamType_Num)
		{
			//���s�̈ʒu�܂œǂݐi�߂�
			fscanf_s(fp, "\n");
			continue;
		}
		//�^�C�v��ۑ�
		TxtParam->Param[Num].Type = (ETextParamType)i;

		// �^�C�v�ɂ���ď����𕪊�
		switch (TxtParam->Param[Num].Type)
		{
		case ETextParamType_Int:			// �����l
											// �^�C�v�����wint�x�������ꍇ�̓p�����[�^������𐮐��l�ɕϊ�����
			TxtParam->Param[Num].Param.Int = atoi(Param1);
			break;

		case ETextParamType_Bool:			// bool�l
											// �^�C�v�����wbool�x�������ꍇ�̓p�����[�^�������bool�l�ɕϊ�����
			TxtParam->Param[Num].Param.Bool = strcmp(Param1, "true") == 0;
			break;

		case ETextParamType_Float:			// ���������_���l
											// �^�C�v�����wfloat�x�������ꍇ�̓p�����[�^������𕂓������_���l�ɕϊ�����
			TxtParam->Param[Num].Param.Float = (float)atof(Param1);
			break;

		case ETextParamType_Vector:			// VECTOR�l
											// �^�C�v�����wvector�x�������ꍇ�͒ǉ��œ�p�����[�^��������擾����
			fscanf_s(fp, "%s %s", Param2, sizeof(Param2), Param3 , sizeof(Param3));

			// �R�̃p�����[�^������𕂓������_���l�ɕϊ�����
			TxtParam->Param[Num].Param.Vector.x = (float)atof(Param1);
			TxtParam->Param[Num].Param.Vector.y = (float)atof(Param2);
			TxtParam->Param[Num].Param.Vector.z = (float)atof(Param3);
			break;

		case ETextParamType_String:			// ������
											// �^�C�v�����wstring�x�������ꍇ�̓p�����[�^����������̂܂ܕۑ�����
			strcpy_s(TxtParam->Param[Num].Param.String, _countof(TxtParam->Param[Num].Param.String), Param1);
			break;

		case ETextParamType_Color:			// �J���[�l
											// �^�C�v�����wcolor�x�������ꍇ�͒ǉ��ŎO�p�����[�^��������擾����
			fscanf_s(fp, "%s %s %s", Param2, sizeof(Param2), Param3, sizeof(Param3), Param4, sizeof(Param4));

			// �S�̃p�����[�^������𐮐��l�ɕϊ�����
			TxtParam->Param[Num].Param.Color.r = atoi(Param1);
			TxtParam->Param[Num].Param.Color.g = atoi(Param2);
			TxtParam->Param[Num].Param.Color.b = atoi(Param3);
			TxtParam->Param[Num].Param.Color.a = atoi(Param4);
			break;
		}

		// �p�����[�^�̐��𑝂₷
		Num++;

		// ���s�̈ʒu�܂œǂݐi�߂�
		fscanf_s(fp, "\n");
	}

	// �p�����[�^�̐���ۑ�
	TxtParam->ParamNum = Num;

	// �t�@�C�������
	fclose(fp);

	// �����I��
	return true;

}

// �w��̖��O�̃p�����[�^�̔z�񒆂̃C���f�b�N�X���擾����
int			TextParam::SearchTextParam(
	//�e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,
	//�p�����[�^��
	const char *ParamName,
	//�p�����[�^�������p�ό���
	...) {
	int     i;
	va_list VaList;
	char    ParamNameS[MAX_PATH];

	// �ό�������p�����[�^���𐶐�����
	va_start(VaList, ParamName);
	vsprintf_s(ParamNameS, ParamName, VaList);
	va_end(VaList);

	// �p�����[�^�̐������J��Ԃ�
	for (i = 0; i < TxtParam->ParamNum; i++)
	{
		// �w��̃p�����[�^���ƈ�v����p�����[�^���������ꍇ�͔z��̃C���f�b�N�X��Ԃ�
		if (strcmp(TxtParam->Param[i].Name, ParamNameS) == 0)
		{
			return i;
		}
	}

	// ������Ȃ������ꍇ�� -1 ��Ԃ�
	return -1;
}

//�w��̖��O��int�^�C�v�̃p�����[�^���擾����
int			TextParam::GetTextParamInt(
	//�e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,

	//�p�����[�^��
	const char *ParamName,

	//�p�����[�^�������p�ό���
	...
) {
	//�ό�������p�����[�^���𐶐����A�p�����[�^�̔z�񒆂�
	//�C���f�b�N�X���擾�����^���������s����
	GETTEXTPARAM_COMMON

		// �p�����[�^��������Ȃ������ꍇ�� 0.0f ��Ԃ�
		if (Index < 0)
		{
			return 0;
		}

	// �p�����[�^�����������ꍇ�́A�p�����[�^�̕��������_���l��Ԃ�
	return TxtParam->Param[Index].Param.Int;
}

//�w��̖��O��float�^�C�v�̃p�����[�^���擾����
float		TextParam::GetTextParamFloat(
	//�e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,

	//�p�����[�^��
	const char *ParamName,

	//�p�����[�^�������p�ό���
	...
) {
	//�ό�������p�����[�^���𐶐����A�p�����[�^�̔z�񒆂�
	//�C���f�b�N�X���擾�����^���������s����
	GETTEXTPARAM_COMMON

	// �p�����[�^��������Ȃ������ꍇ�� 0.0f ��Ԃ�
	if (Index < 0)
	{
		return 0.0f;
	}

	// �p�����[�^�����������ꍇ�́A�p�����[�^�̕��������_���l��Ԃ�
	return TxtParam->Param[Index].Param.Float;

}

// �w��̖��O��vector�^�C�v�̃p�����[�^���擾����
//     �߂�l : �p�����[�^��VECTOR�l
VECTOR      TextParam::GetTextParamVector(
	// �e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,

	// �p�����[�^��
	const char *ParamName,

	// �p�����[�^�������p�ό���
	...
)
{
	// �ό�������p�����[�^���𐶐����A�p�����[�^�̔z�񒆂�
	// �C���f�b�N�X���擾�����^���������s����
	GETTEXTPARAM_COMMON

		// �p�����[�^��������Ȃ������ꍇ�� x=0.0f, y=0.0f, z=0.0f ��Ԃ�
		if (Index < 0)
		{
			return VGet(0.0f, 0.0f, 0.0f);
		}

	// �p�����[�^�����������ꍇ�́A�p�����[�^��VECTOR�l��Ԃ�
	return TxtParam->Param[Index].Param.Vector;
}

//�w��̖��O��siring�^�C�v�̃p�����[�^���擾����
const char		*TextParam::GetTextParamString(
	//�e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,

	//�p�����[�^��
	const char *ParamName,

	//�p�����[�^�������p�ό���
	...
) {
	//�ό�������p�����[�^���𐶐����A�p�����[�^�̔z�񒆂�
	//�C���f�b�N�X���擾�����^���������s����
	GETTEXTPARAM_COMMON

		// �p�����[�^��������Ȃ������ꍇ�� 0.0f ��Ԃ�
		if (Index < 0)
		{
			return NULL;
		}

	// �p�����[�^�����������ꍇ�́A�p�����[�^�̕�����̃A�h���X��Ԃ�
	return TxtParam->Param[Index].Param.String;

}

// �w��̖��O��color�^�C�v�̃p�����[�^���擾����
//     �߂�l : �p�����[�^��COLOR_U8�l
COLOR_U8    TextParam::GetTextParamColor(
	// �e�L�X�g�p�����[�^���\���̂̃A�h���X
	STextParamInfo *TxtParam,

	// �p�����[�^��
	const char *ParamName,

	// �p�����[�^�������p�ό���
	...
)
{
	// �ό�������p�����[�^���𐶐����A�p�����[�^�̔z�񒆂�
	// �C���f�b�N�X���擾�����^���������s����
	GETTEXTPARAM_COMMON

		// �p�����[�^��������Ȃ������ꍇ�� r=0 g=0 b=0 a=0 ��Ԃ�
		if (Index < 0)
		{
			return GetColorU8(0, 0, 0, 0);
		}

	// �p�����[�^�����������ꍇ�́A�p�����[�^��COLOR_U8�̒l��Ԃ�
	return TxtParam->Param[Index].Param.Color;
}