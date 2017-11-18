#include "Camera.h"

Camera::Camera(){

	//�J�����|�W�V��������уJ�����^�[�Q�b�g�ݒ�
	//cpos = VGet(600.0f, 600.0f, -400.0f);
	//ctgt = VGet(600.0f, 300.0f, -400.0f);



	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	//SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera(){



}

//��]�֐� (x,z)�̓_��(mx,mz)�𒆐S��ang�p��]����
void Camera::rotate(float *x,float *z, const float ang, float mx, float mz) {
	const float ox = *x - mx, oz = *z - mz;
	*x = ox * cos(ang) + oz * sin(ang);
	*z = -ox * sin(ang) + oz * cos(ang);
	*x += mx;
	*z += mz;
}

//�J������]�����֐��B
void Camera::cameraRotate(float tagX,float tagZ) {

	// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
	//	SetCameraNearFar(1.0f, 1000.0f);

	//�������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTargetAndUpVec(VGet(cameraX, 150.0f, cameraZ),VGet( tagX, 150.0f ,tagZ), VGet(0.0f, 1.0f, 0.0f));

	//�p�b�h����
	cpad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (cpad & PAD_INPUT_L) {//���L�[��������Ă�����
		rotate(&cameraX, &cameraZ, +ROTATE_SPEED, tagX, tagZ);//��]
	}
	if (cpad & PAD_INPUT_R) {//�E�L�[��������Ă�����
		rotate(&cameraX, &cameraZ, -ROTATE_SPEED, tagX, tagZ);//��]
	}
}

//�J�����ړ�����
void Camera::cameraMove(float tagX, float tagZ) {

	cameraX = tagX - 700 * cos(ctArg(tagX,tagZ));
	cameraZ = tagZ - 700 * sin(ctArg(tagX,tagZ));

}

//�J�����ƃ^�[�Q�b�g�̊p�x�v�Z
float Camera::ctArg(float tagX, float tagZ) {

	return atan2((tagZ - cameraZ) , (tagX -cameraX));
	
}


//�J������x���W��Ԃ��֐�
float Camera::cameraPositionX(){
	
	return cameraX;

}

//�J������z���W��Ԃ��֐�
float Camera::cameraPositionZ(){

	return cameraZ;

}