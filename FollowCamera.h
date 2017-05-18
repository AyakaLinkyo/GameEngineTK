//��----------------------------------------------------��
//��*�t�@�C�����FFollowCamera.h							��
//��*���e�@�@�@�F���@�ɒǏ]����J�����N���X				��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.15								��
//��----------------------------------------------------��

#pragma once
#include "Camera.h"
class FollowCamera :
	public Camera
{
public:
	//���@�ƃJ�����̋���
	static const float CAMERA_DISTANCE;	
	//�R���X�g���N�^
	FollowCamera(int width, int height);
	//���t���[���X�V
	void Update() override;

	//�Ǐ]�Ώۂ̍��W���Z�b�g
	void Set_target_pos(const DirectX::SimpleMath::Vector3& target_pos);
	//�Ǐ]�Ώۂ̊p�x���Z�b�g
	void Set_target_rotate(float target_rotate);


protected:
	//�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	//�Ǐ]�Ώۂ̉�]�p
	float m_target_rotate;

};

