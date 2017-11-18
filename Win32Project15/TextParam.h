#ifndef _TEXTPARAM_H
#define _TEXTPARAM_H

#include "DxLib.h"

//�e�L�X�g�p�����[�^�̖��O�Ɏg����ő啶����
#define TEXTPARAM_NAME_MAXLENGTH		64

// �t�@�C����Ɋ܂߂���e�L�X�g�p�����[�^�̍ő吔
#define TEXTPARAM_MAXNUM				1024

// ������^�C�v�̃p�����[�^�̍ő啶����
#define TEXTPARAM_STRING_MAXLENGTH		64

//�p�����[�^�^�C�v
typedef enum _ETextParamType
{
	ETextParamType_Int,				// �����l
	ETextParamType_Bool,			// bool�l
	ETextParamType_Float,			// ���������_���l
	ETextParamType_Vector,			// VECTOR�l
	ETextParamType_String,			// ������
	ETextParamType_Color,			// �J���[�l

	ETextParamType_Num,				// �p�����[�^�^�C�v�̐�
} ETextParamType;

class TextParam {

public:

	TextParam();

	~TextParam();

	//�p�����[�^�{�̂̋��p��
	union STextParam
	{
		//int�^�C�v�̃p�����[�^�p�ϐ�
		int                Int;

		//bool�^�C�v�̃p�����[�^�p�ϐ�
		bool               Bool;

		//float�^�C�v�̃p�����[�^�p�ϐ�
		float              Float;

		//vector�^�C�v�̃p�����[�^�p�ϐ�
		VECTOR             Vector;

		//string�^�C�v�̃p�����[�^�p�ϐ�
		char               String[TEXTPARAM_STRING_MAXLENGTH];

		//color�^�C�v�̃p�����[�^�p�ϐ�
		COLOR_U8           Color;
	} sTextParam;

	//�p�����[�^��̏��
	struct STextParamInfoUnit
	{
		//�p�����[�^�̖��O
		char               Name[TEXTPARAM_NAME_MAXLENGTH];

		//�p�����[�^�^�C�v
		ETextParamType     Type;

		//�p�����[�^�{��
		STextParam         Param;
	} sTextParamInfoUnit;

	//�P�t�@�C���̃e�L�X�g�p�����[�^���
	struct STextParamInfo
	{
		// �p�����[�^�̐�
		int                ParamNum;

		//�p�����[�^�z��
		STextParamInfoUnit Param[TEXTPARAM_MAXNUM];
	} sTextParamInfo;



	//�p�����[�^�t�@�C����ǂݍ���
	bool        LoadTextParam(
		// �e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,
		// �t�@�C���p�X
		const char *FilePath,
		// �t�@�C���p�X�����p�ό���
		...);

	//�w��̖��O�̃p�����[�^�̔z�񒆂̃C���f�b�N�X���擾����
	int		SearchTextParam(
		//�e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,
		//�p�����[�^��
		const char *ParamName,
		//�p�����[�^�������p�ό���
		...
	);

	//�w��̖��O��int�^�C�v�̃p�����[�^���擾����
	int		GetTextParamInt(
		//�e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,

		//�p�����[�^��
		const char *ParamName,

		//�p�����[�^�������p�ό���
		...
	);

	//�w��̖��O��float�^�C�v�̃p�����[�^���擾����
	float		GetTextParamFloat(
		//�e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,

		//�p�����[�^��
		const char *ParamName,

		//�p�����[�^�������p�ό���
		...
		);

	// �w��̖��O��vector�^�C�v�̃p�����[�^���擾����
	//     �߂�l : �p�����[�^��VECTOR�l
	VECTOR      GetTextParamVector(
		// �e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,

		// �p�����[�^��
		const char *ParamName,

		// �p�����[�^�������p�ό���
		...
	);

	//�w��̖��O��String�^�C�v�̃p�����[�^���擾����
	const char		*GetTextParamString(
		//�e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,

		//�p�����[�^��
		const char *ParamName,

		//�p�����[�^�������p�ό���
		...
	);

	// �w��̖��O��color�^�C�v�̃p�����[�^���擾����
	//     �߂�l : �p�����[�^��COLOR_U8�l
	COLOR_U8    GetTextParamColor(
		// �e�L�X�g�p�����[�^���\���̂̃A�h���X
		STextParamInfo *TxtParam,

		// �p�����[�^��
		const char *ParamName,

		// �p�����[�^�������p�ό���
		...
	);

};

#endif
