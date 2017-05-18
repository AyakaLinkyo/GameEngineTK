
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
}

void FollowCamera::Update()
{
	//���_�A�Q�Ɠ_
	Vector3 eyepos, refpos;

	//�^�[�Q�b�g�̍��W�͎��@�̍��W�ɒǏ]
	refpos = m_target_pos + Vector3(0, 2.0f, 0);
	//�^�[�Q�b�g���W����J�������W�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	//�J�����̎��������̋t�����ɉ�]
	Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	//���_���W���v�Z
	eyepos = refpos + cameraV;

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
