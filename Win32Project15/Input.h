#ifndef _INPUT_H
#define _INPUT_H

#include "DxLib.h"

//チェックするゲームパッドの数
#define		MAX_GAMEPAD_NUM		16

// キーボードの入力状態を取得するためのバッファのサイズ
#define		KEY_STATE_BUFFER_SIZE	256

class Input {

		//入力情報
		typedef enum _EInputType
		{
			EInputType_Left,				// 方向入力左
			EInputType_Right,				// 方向入力右
			EInputType_Up,					// 方向入力上
			EInputType_Down,				// 方向入力下

			EInputType_Camera_Left,			// カメラ用方向入力左
			EInputType_Camera_Right,		// カメラ用方向入力右
			EInputType_Camera_Up,			// カメラ用方向入力上
			EInputType_Camera_Down,			// カメラ用方向入力下

			EInputType_Attack,				// 攻撃ボタン
			EInputType_Defence,				// 防御ボタン
			EInputType_Jump,				// ジャンプボタン
			EInputType_Pause,				// ポーズボタン

			EInputType_Num,					// 入力タイプの数
		} EInputType;
		
		//DirectInputの入力情報タイプ
		typedef enum _EDInputType
		{
			EDInputType_X,					// スティックのＸ軸
			EDInputType_Y,					// スティックのＹ軸
			EDInputType_Z,					// スティックのＺ軸
			EDInputType_Rx,					// スティックのＸ軸回転
			EDInputType_Ry,					// スティックのＹ軸回転
			EDInputType_Rz,					// スティックのＺ軸回転
			EDInputType_POV,				// 方向コントローラ
			EDInputType_Button,				// ボタン
		} EDInputType;

		//ゲームでの入力とキーやパッドなどの入力との対応情報
		struct SInputTypeInfo
		{
			//パッド番号
			int              PadNo;

			//DirectInput の入力情報タイプ
			EDInputType      DirectInputType;

			//サブ情報( DirectInputType によって意味が変わる )
			int              SubInfo[2];

			//対応するキーボードのキー( KEY_INPUT_UP など )
			int              KeyInput;
		} g_InpTyInf;

		//入力処理用の情報
		struct SInputSystemData {

			//ゲーム中の入力とキーやパッドなどの入力との対応情報
			SInputTypeInfo   InputTypeInfo[EInputType_Num];

			// DirectInput のパッドの入力状態
			DINPUT_JOYSTATE  DirectInputState[MAX_GAMEPAD_NUM];

			//キーの入力状態
			char             KeyInput[KEY_STATE_BUFFER_SIZE];

			//ボタンの入力状態
			int              ButtonInput;

			//ボタンの押された瞬間のみの入力状態
			int              ButtonEdgeInput;

			//カメラ操作用のスティック入力状態
			VECTOR           CameraStickInput;

		} g_InpSys;

	public:

		Input();

		~Input();

		//入力処理
		void ProcessInput();

};

#endif
