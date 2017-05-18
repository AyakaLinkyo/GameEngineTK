
#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;	

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_rotate = 0.0f;
	m_keyboard = nullptr;
	camera_flag = true;
}

void FollowCamera::Update()
{
	//�L�[�{�[�h�̏��擾
	Keyboard::State keyboard_state = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboard_state);

	//C���������т�FPS/TPS�����ւ���
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		//�t���O�̐؂�ւ�
		if (camera_flag)
		{
			camera_flag = false;
		}
		else
		{
			camera_flag = true;
		}
	}

	//���_�A�Q�Ɠ_
	Vector3 eyepos, refpos;

	if(camera_flag)
	{
		//TPS�J��������
		//�^�[�Q�b�g�̍��W�͎��@�̍��W�ɒǏ]
		refpos = m_target_pos + Vector3(0, 2.0f, 0);
		//�^�[�Q�b�g���W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	
		//�J�����̎��������̋t�����ɉ�]
		Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
	
		//���_���W���v�Z
		eyepos = refpos + cameraV;
		//���_�����݈ʒu�����Ԃ���
		//���̎��_�����̎��_+(���̎��_-���̎��_)*��Ԋ���
		eyepos = Camera::eyepos + (eyepos - Camera::eyepos) * 0.05f;
	
		//�Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = Camera::refpos + (refpos - Camera::refpos) * 0.2f;
	}

	else
	{//FPS�J����
	//���@�̖ڂ̈ʒu����������_�Ƃ���
		Vector3 position;
		position = m_target_pos + Vector3(0, 0.2f, 0);
		//eyepos = m_target_pos + Vector3(0, 0.2f, 0);
		//�^�[�Q�b�g���W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
		//�J�����̎��������̋t�����ɉ�]
		Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV*0.1f;

		//�Q�Ɠ_���W���v�Z
		refpos = position + cameraV;

	}


	//�J�����ɏ��Z�b�g
	SetEyepos(eyepos);
	SetRefpos(refpos);

	//���N���X�̍X�V
	Camera::Update();

}

void FollowCamera::Set_target_pos(const DirectX::SimpleMath::Vector3 & target_pos)
{
	this->m_target_pos = target_pos;
}

void FollowCamera::Set_target_rotate(float target_rotate)
{
	this->m_target_rotate = target_rotate;
}

void FollowCamera::Set_keyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
