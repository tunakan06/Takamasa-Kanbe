#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "DxLib.h"
#include <math.h>
#include "TextParam.h"
#include "Animation.h"
#include "Camera.h"

#include "Enemy.h"
#include "Player.h"


class Character {

public:

	enum CharacterType{
	
		Chara_Player,
		Chara_Enemy_Monster,

		Chara_Num,

	};

	Character();

	~Character();

	//キャラクター処理
	void Process( float steptime, int stg );

	//キャラクターの体力ゲージの処理の準備


private:

	Camera* mCamera;
	Enemy*	mEnemy;
	Player*	mPlayer;

	float		playerposX;
	float		playerposZ;

	float		cameraposX;
	float		cameraposZ;

	float		arg;

};

#endif
