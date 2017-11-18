#ifndef _TEXTPARAM_H
#define _TEXTPARAM_H

#include "DxLib.h"

//テキストパラメータの名前に使える最大文字数
#define TEXTPARAM_NAME_MAXLENGTH		64

// ファイル一つに含められるテキストパラメータの最大数
#define TEXTPARAM_MAXNUM				1024

// 文字列タイプのパラメータの最大文字数
#define TEXTPARAM_STRING_MAXLENGTH		64

//パラメータタイプ
typedef enum _ETextParamType
{
	ETextParamType_Int,				// 整数値
	ETextParamType_Bool,			// bool値
	ETextParamType_Float,			// 浮動小数点数値
	ETextParamType_Vector,			// VECTOR値
	ETextParamType_String,			// 文字列
	ETextParamType_Color,			// カラー値

	ETextParamType_Num,				// パラメータタイプの数
} ETextParamType;

class TextParam {

public:

	TextParam();

	~TextParam();

	//パラメータ本体の共用体
	union STextParam
	{
		//intタイプのパラメータ用変数
		int                Int;

		//boolタイプのパラメータ用変数
		bool               Bool;

		//floatタイプのパラメータ用変数
		float              Float;

		//vectorタイプのパラメータ用変数
		VECTOR             Vector;

		//stringタイプのパラメータ用変数
		char               String[TEXTPARAM_STRING_MAXLENGTH];

		//colorタイプのパラメータ用変数
		COLOR_U8           Color;
	} sTextParam;

	//パラメータ一つの情報
	struct STextParamInfoUnit
	{
		//パラメータの名前
		char               Name[TEXTPARAM_NAME_MAXLENGTH];

		//パラメータタイプ
		ETextParamType     Type;

		//パラメータ本体
		STextParam         Param;
	} sTextParamInfoUnit;

	//１ファイルのテキストパラメータ情報
	struct STextParamInfo
	{
		// パラメータの数
		int                ParamNum;

		//パラメータ配列
		STextParamInfoUnit Param[TEXTPARAM_MAXNUM];
	} sTextParamInfo;



	//パラメータファイルを読み込む
	bool        LoadTextParam(
		// テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,
		// ファイルパス
		const char *FilePath,
		// ファイルパス生成用可変個引数
		...);

	//指定の名前のパラメータの配列中のインデックスを取得する
	int		SearchTextParam(
		//テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,
		//パラメータ名
		const char *ParamName,
		//パラメータ名生成用可変個引数
		...
	);

	//指定の名前のintタイプのパラメータを取得する
	int		GetTextParamInt(
		//テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,

		//パラメータ名
		const char *ParamName,

		//パラメータ名生成用可変個引数
		...
	);

	//指定の名前のfloatタイプのパラメータを取得する
	float		GetTextParamFloat(
		//テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,

		//パラメータ名
		const char *ParamName,

		//パラメータ名生成用可変個引数
		...
		);

	// 指定の名前のvectorタイプのパラメータを取得する
	//     戻り値 : パラメータのVECTOR値
	VECTOR      GetTextParamVector(
		// テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,

		// パラメータ名
		const char *ParamName,

		// パラメータ名生成用可変個引数
		...
	);

	//指定の名前のStringタイプのパラメータを取得する
	const char		*GetTextParamString(
		//テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,

		//パラメータ名
		const char *ParamName,

		//パラメータ名生成用可変個引数
		...
	);

	// 指定の名前のcolorタイプのパラメータを取得する
	//     戻り値 : パラメータのCOLOR_U8値
	COLOR_U8    GetTextParamColor(
		// テキストパラメータ情報構造体のアドレス
		STextParamInfo *TxtParam,

		// パラメータ名
		const char *ParamName,

		// パラメータ名生成用可変個引数
		...
	);

};

#endif
