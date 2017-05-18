//��----------------------------------------------------��
//��*�t�@�C�����FFollowCamera.h							��
//��*���e�@�@�@�F���@�ɒǏ]����J�����N���X				��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.15								��
//��----------------------------------------------------��

#pragma once
#include "Camera.h"
#include <Keyboard.h>
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
	//�L�[�{�[�h���Z�b�g
	void Set_keyboard(DirectX::Keyboard* keyboard);

protected:
	//�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	//�Ǐ]�Ώۂ̉�]�p
	float m_target_rotate;
	//�L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	//FPS/TPS�J�����؂�ւ�
	bool camera_flag;
};

