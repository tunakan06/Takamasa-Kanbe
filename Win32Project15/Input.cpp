#include "Input.h"

//パッドの識別子テーブル
static int g_PadIDTable[MAX_GAMEPAD_NUM] = {

	DX_INPUT_PAD1,
	DX_INPUT_PAD2,
	DX_INPUT_PAD3,
	DX_INPUT_PAD4,
	DX_INPUT_PAD5,
	DX_INPUT_PAD6,
	DX_INPUT_PAD7,
	DX_INPUT_PAD8,
	DX_INPUT_PAD9,
	DX_INPUT_PAD10,
	DX_INPUT_PAD11,
	DX_INPUT_PAD12,
	DX_INPUT_PAD13,
	DX_INPUT_PAD14,
	DX_INPUT_PAD15,
	DX_INPUT_PAD16,

};

Input::Input(){}

Input::~Input(){}


//入力処理
void Input::ProcessInput() {

	int	PadNum;
	int	i;

	//パッドの数を取得する
	PadNum = GetJoypadNum();

	if (PadNum > MAX_GAMEPAD_NUM) {

		PadNum = MAX_GAMEPAD_NUM;

	}

	//パッドの入力情報をDirectInputから取得
	for (i = 0; i < PadNum; i++) {

		GetJoypadDirectInputState( g_PadIDTable[i] , &g_InpSys.DirectInputState[i] );
	}

	//現在のキーの入力状態を取得する
	GetHitKeyStateAll( g_InpSys.KeyInput );



}