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

	//�L�����N�^�[����
	void Process( float steptime, int stg );

	//�L�����N�^�[�̗̑̓Q�[�W�̏����̏���


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
