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
	virtual void Update();

	//�r���[�s����擾����֐�
	const DirectX::SimpleMath::Matrix& GetViewMatrix();
	//�ˉe�s����擾����֐�
	const DirectX::SimpleMath::Matrix& GetProjMatrix();
	//���_���Z�b�g
	void SetEyepos(const DirectX::SimpleMath::Vector3& eyepos);
	//�Q�Ɠ_���Z�b�g
	void SetRefpos(const DirectX::SimpleMath::Vector3& refpos);
	//������x�N�g�����Z�b�g
	void SetUppos(const DirectX::SimpleMath::Vector3& uppos);

	//������������p���Z�b�g
	void SetForY(float fovY);

	//������������p���Z�b�g
	void SetAspect(float aspect);

	//������������p���Z�b�g
	void SetNearClip(float nearclip);

	//������������p���Z�b�g
	void SetFarClip(float farclip);

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

