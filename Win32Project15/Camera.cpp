#include "Camera.h"

Camera::Camera(){

	//カメラポジションおよびカメラターゲット設定
	//cpos = VGet(600.0f, 600.0f, -400.0f);
	//ctgt = VGet(600.0f, 300.0f, -400.0f);



	//奥行0.1～1000までをカメラの描画範囲とする
	//SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera(){



}

//回転関数 (x,z)の点を(mx,mz)を中心にang角回転する
void Camera::rotate(float *x,float *z, const float ang, float mx, float mz) {
	const float ox = *x - mx, oz = *z - mz;
	*x = ox * cos(ang) + oz * sin(ang);
	*z = -ox * sin(ang) + oz * cos(ang);
	*x += mx;
	*z += mz;
}

//カメラ回転処理関数。
void Camera::cameraRotate(float tagX,float tagZ) {

	// カメラの 手前クリップ距離と 奥クリップ距離を設定する
	//	SetCameraNearFar(1.0f, 1000.0f);

	//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTargetAndUpVec(VGet(cameraX, 150.0f, cameraZ),VGet( tagX, 150.0f ,tagZ), VGet(0.0f, 1.0f, 0.0f));

	//パッド操作
	cpad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (cpad & PAD_INPUT_L) {//左キーが押されていたら
		rotate(&cameraX, &cameraZ, +ROTATE_SPEED, tagX, tagZ);//回転
	}
	if (cpad & PAD_INPUT_R) {//右キーが押されていたら
		rotate(&cameraX, &cameraZ, -ROTATE_SPEED, tagX, tagZ);//回転
	}
}

//カメラ移動処理
void Camera::cameraMove(float tagX, float tagZ) {

	cameraX = tagX - 700 * cos(ctArg(tagX,tagZ));
	cameraZ = tagZ - 700 * sin(ctArg(tagX,tagZ));

}

//カメラとターゲットの角度計算
float Camera::ctArg(float tagX, float tagZ) {

	return atan2((tagZ - cameraZ) , (tagX -cameraX));
	
}


//カメラのx座標を返す関数
float Camera::cameraPositionX(){
	
	return cameraX;

}

//カメラのz座標を返す関数
float Camera::cameraPositionZ(){

	return cameraZ;

}