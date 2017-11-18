#ifndef _CAMERA_H
#define _CAMERA_H

#include "DxLib.h"
#include <math.h>

static const float ROTATE_SPEED = DX_PI_F / 90;//��]�X�s�[�h

class Camera {

	//�J�����ʒu�ϐ�
	VECTOR cpos;

	//�J�����^�[�Q�b�g�ʒu�ϐ�
	VECTOR ctgt;

	//�J�������[�N�p�b�h�ϐ�
	int cpad;

	float cameraX = 0.0f, cameraZ = -50.0f;    //�J�����̍��W
	const float targetX = 0.0f, targetZ = 0.0f;//�J�����̎����̐�^�[�Q�b�g�̍��W

public:

	Camera();

	~Camera();

	//��]�֐��B(x,z)�̓_��(mx,mz)�𒆐S��ang�p��]����
	void rotate(float *x, float *z, const float ang, const float mx, const float mz);

	//�J������]�����֐��B
	void cameraRotate(float tagX, float tagZ);

	//�J�����ړ�����
	void cameraMove(float tagX, float tagZ);

	//�J�����ƃ^�[�Q�b�g�̊p�x�v�Z
	float ctArg(float tagX, float tagZ);

	//�J������x���W��Ԃ��֐�
	float cameraPositionX();

	//�J������z���W��Ԃ��֐�
	float cameraPositionZ();


};

#endif
