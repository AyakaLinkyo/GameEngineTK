//��----------------------------------------------------��
//��*�t�@�C�����FCamera.h								��
//��*���e�@�@�@�F�J�����N���X�̃w�b�_�[					��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.11								��
//��----------------------------------------------------��

#pragma once
#include <SimpleMath.h>



class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	//�X�V
	void Update();

	//�r���[�s����擾����֐�
	DirectX::SimpleMath::Matrix GetViewMatrix();
	//�ˉe�s����擾����֐�
	DirectX::SimpleMath::Matrix GetProjMatrix();
	//���_���Z�b�g
	void SetEyepos(DirectX::SimpleMath::Vector3 eyepos);

protected:
	//�r���[�s��
	DirectX::SimpleMath::Matrix view;
	//�ǂ����猩��̂��i���_�j
	DirectX::SimpleMath::Vector3 eyepos;
	//�ǂ�������̂��i�����_/�Q�Ɠ_�j
	DirectX::SimpleMath::Vector3 refpos;
	//�ǂ��炪��ʏ�������i������x�N�g���j
	DirectX::SimpleMath::Vector3 upvec;


	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix proj;

	//������������p
	float fovY;
	//�A�X�y�N�g��i���Əc�̔䗦�j
	float aspect;
	//��O�̕\�����E����
	float nearclip;
	//���̕\�����E����
	float farclip;

};

