#ifndef _CAMERA_H
#define _CAMERA_H

#include "DxLib.h"
#include <math.h>

static const float ROTATE_SPEED = DX_PI_F / 90;//回転スピード

class Camera {

	//カメラ位置変数
	VECTOR cpos;

	//カメラターゲット位置変数
	VECTOR ctgt;

	//カメラワークパッド変数
	int cpad;

	float cameraX = 0.0f, cameraZ = -50.0f;    //カメラの座標
	const float targetX = 0.0f, targetZ = 0.0f;//カメラの視線の先ターゲットの座標

public:

	Camera();

	~Camera();

	//回転関数。(x,z)の点を(mx,mz)を中心にang角回転する
	void rotate(float *x, float *z, const float ang, const float mx, const float mz);

	//カメラ回転処理関数。
	void cameraRotate(float tagX, float tagZ);

	//カメラ移動処理
	void cameraMove(float tagX, float tagZ);

	//カメラとターゲットの角度計算
	float ctArg(float tagX, float tagZ);

	//カメラのx座標を返す関数
	float cameraPositionX();

	//カメラのz座標を返す関数
	float cameraPositionZ();


};

#endif
