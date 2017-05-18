//��----------------------------------------------------��
//��*�t�@�C�����FCamera.h								��
//��*���e�@�@�@�F�J�����𐧌䂷��N���X					��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.11								��
//��----------------------------------------------------��

#include "pch.h"
#include "Camera.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


//��----------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
Camera::Camera(int width, int height)
{
	//�����o�ϐ��̏�����
	//�r���[�s��
	//�ǂ����猩��̂��i���_�j
	eyepos = Vector3(0, 0, 5);
	//�ǂ�������̂��i�����_/�Q�Ɠ_�j
	refpos = Vector3(0, 0, 10);
	//�ǂ��炪��ʏ�������i������x�N�g���j
	upvec = Vector3(0, 1, 0);
	//�x�N�g���̐��K���i�������P�ɂ���j
	upvec.Normalize();

	//�v���W�F�N�V�����s��
	//������������p
	fovY = XMConvertToRadians(60.0f);
	//�A�X�y�N�g��i���Əc�̔䗦�j
	aspect = (float)width / height;
	//��O�̕\�����E����
	nearclip = 0.1f;
	//���̕\�����E����
	farclip = 1000.0f;

	//�r���[�s����쐬
	view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	//�ˉe�s��̐����i�������e�p�j
	proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

}


Camera::~Camera()
{
}

void Camera::Update()
{
	//�r���[�s����쐬
	view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	//�ˉe�s��̐����i�������e�p�j
	proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

}

const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{	
	////�r���[�s����쐬
	//view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	return view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProjMatrix()
{
	////�ˉe�s��̐����i�������e�p�j
	//proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

	return proj;
}

void Camera::SetEyepos(const DirectX::SimpleMath::Vector3& eyepos)
{
	this->eyepos = eyepos;
}

void Camera::SetRefpos(const DirectX::SimpleMath::Vector3 & refpos)
{
	this->refpos = refpos;
}

void Camera::SetUppos(const DirectX::SimpleMath::Vector3 & uppos)
{
	this->upvec = uppos;
}

void Camera::SetForY(float fovY)
{
	this->fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	this->aspect = aspect;
}

void Camera::SetNearClip(float nearclip)
{
	this->nearclip = nearclip;
}

void Camera::SetFarClip(float farclip)
{
	this->farclip = farclip;
}
