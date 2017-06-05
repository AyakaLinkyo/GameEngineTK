#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//��----------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��----------------------------------------------------��
ENEMY::ENEMY()
{
	//���@�p�[�c�̓ǂݍ���
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].LoadModel(L"Resources/down_body.cmo");
	m_ObjEnemy[ENEMY_PARTS_WEAPON].LoadModel(L"Resources/weapon.cmo");


	//�p�[�c�̐e�q�֌W���Z�b�g
	m_ObjEnemy[ENEMY_PARTS_HEAD].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);

	m_ObjEnemy[ENEMY_PARTS_WEAPON].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);

	vec = Vector3(rand() % 100 + 1, 0, rand() % 100 + 1);

	//�e����̃I�t�Z�b�g
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(vec);
	m_ObjEnemy[ENEMY_PARTS_HEAD].Set_trans(Vector3(0, 1.5, 0));
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].Set_trans(Vector3(0, 0, 0));
	m_ObjEnemy[ENEMY_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));

	////���[�ځ[�ǂ̏�����
	//this->keyboard = keyboard;


	m_timer = 0;
	m_DistAngle = 0;
}

//��----------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
ENEMY::~ENEMY()
{
}


void ENEMY::Init()
{
}

//��----------------------------------------------------��
//��*func�F��i
//��*arg�F����I�u�W�F�N�g,�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void ENEMY::Update()
{
	//����I�ɐi�s������ς���
	m_timer--;
	if (m_timer < 0)
	{
		m_timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;
		m_DistAngle += rnd;
	}

	//�ڕW�p�x�Ɍ������āA�@�̂̊p�x�����킶����
	{
		Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate();

		//�ڕW�p�x�ւ́A�ŒZ�p�x���擾
		float angle = GetShortAngleRad(rotv.y, XMConvertToRadians(m_DistAngle));
		rotv.y += angle*0.01f;
		m_ObjEnemy[ENEMY_PARTS_BODY].Set_rotate(rotv);
	}
	//�@�̂̌����Ă�������ɐi��
	{
		//���̍��W���擾
		Vector3 trans = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();

		Vector3 move(0, 0, -0.02f);
		Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate();
		Matrix rotm = Matrix::CreateRotationY(rotv.y);
		move = Vector3::TransformNormal(move, rotm);

		//���W���ړ�
		trans += move;
		//�ړ���̍��W���Z�b�g
		m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(trans);
	}

	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Update();
	}


}

void ENEMY::Render()
{
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin(); it != m_ObjEnemy.end(); it++)
	{
		it->Draw();
	}

}
//��----------------------------------------------------��
//��*func�F�O�i
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void ENEMY::Advance()
{
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(pos + moveV);
}

//��----------------------------------------------------��
//��*func�F��i
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void ENEMY::Back()
{
	Vector3 moveV(0, 0, 0.1f);
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(pos + moveV);

}

//��----------------------------------------------------��
//��*func�F����]
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void ENEMY::LeftRotation()
{
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_rotate(Vector3(0, angle + 0.01f, 0));
}

//��----------------------------------------------------��
//��*func�F�E��]
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void ENEMY::RightRotation()
{
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_rotate(Vector3(0, angle - 0.01f, 0));
}

DirectX::SimpleMath::Vector3 ENEMY::Get_scale()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].Get_scale();
}

float ENEMY::Get_rotate()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;
}

DirectX::SimpleMath::Vector3 ENEMY::Get_transmat()
{
	return m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();
}

float ENEMY::GetShortAngleRad(float now_rot, float target_rot)
{
	float rotate;
	rotate = target_rot - now_rot;
	return rotate;
}

