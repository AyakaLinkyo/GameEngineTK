#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//��----------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��----------------------------------------------------��
Player::Player(DirectX::Keyboard* keyboard)
{
	//���@�p�[�c�̓ǂݍ���
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].LoadModel(L"Resources/down_body.cmo");
	m_ObjPlayer[PLAYER_PARTS_WEAPON].LoadModel(L"Resources/weapon.cmo");


	//�p�[�c�̐e�q�֌W���Z�b�g
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	m_ObjPlayer[PLAYER_PARTS_HEAD].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	//�e����̃I�t�Z�b�g
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(0, 0.35, 0));
	m_ObjPlayer[PLAYER_PARTS_HEAD].Set_trans(Vector3(0, 1.5, 0));
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].Set_trans(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));

	//*----------------------------------------------------------------------*//
	//���ꂼ��̃��[�V�����Ɏg�p����t���O�A�J�E���g�̏�����

	m_attack = false;		//�U���t���O
	m_attack_cnt = 0;		//�U���J�E���g

	m_defense = false;		//�h��t���O
	m_defense_cnt = 0;		//�h��J�E���g

	m_jump = false;			//�W�����v�t���O
	m_jump_cnt = 0;			//�W�����v�J�E���g
	jumping = 0.0f;			//�����x�N�g���̏�����
//*----------------------------------------------------------------------*//


	//���[�ځ[�ǂ̏�����
	this->keyboard = keyboard;
	keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	std::unique_ptr<Keyboard::KeyboardStateTracker> keyTracker(new Keyboard::KeyboardStateTracker);
	//���˒��ł͂Ȃ�
	m_FireFlag = false;

	//�e�ۗp�̓����蔻���ݒ�
	{
		m_collisionNodeBullet.Initialize();
		//�e�p�[�c�̎w��
		m_collisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_WEAPON]);
		m_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_collisionNodeBullet.SetLocalRadius(1.0f);
	}
}

//��----------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
Player::~Player()
{
}


void Player::Init()
{
}

//��----------------------------------------------------��
//��*func�F��i
//��*arg�F����I�u�W�F�N�g,�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Update()
{
	//�L�[�{�[�h�̏��擾
	Keyboard::State key = keyboard->GetState();
	keyTracker->Update(key);


	//�U�����[�V����
	if (m_attack)
	{
		//���i�r�j��O�ɓ˂��o��
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans((Vector3(0, 0.35, 0)) + Vector3(0.5, 0.5, -1.0));

		//�J�E���g�ǉ�
		m_attack_cnt++;

		//�Q�O�t���[����
		if (m_attack_cnt > 20)
		{
			//���i�r�j�����Ƃɖ߂�
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));
			//�t���O��OFF�ɂ���
			m_attack = false;
			//�J�E���g�̏�����
			m_attack_cnt = 0;
		}

	}

	//�h�䃂�[�V����
	if (m_defense)
	{
		//������]������i�h��p���p�j
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotate(Vector3(5.0, 2.0, 3.0));
		//����O�ɓ˂��o��
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans((Vector3(0, 0.35, 0)) + Vector3(0.5, 0.5, -1.0));

		//�J�E���g����
		m_defense_cnt++;

		//�Q�O�t���[����
		if (m_defense_cnt > 20)
		{
			//���̉�]�����Ƃɖ߂�
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotate(Vector3(0.0, 0.0, 0.0));
			//���̈ʒu��߂�
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));
			//�t���O�̏�����
			m_defense = false;
			//�J�E���g�̏�����
			m_defense_cnt = 0;
		}

	}
	//�W�����v���[�V����
	if (m_jump)
	{
		if (m_jump_cnt == 0)
		{
			vec = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
		}
		//�J�E���g���Q�O�t���[���ȉ��̏ꍇ
		if (m_jump_cnt < 20)
		{
			//��ɃW�����v����
			m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec + Vector3(0.0, jumping, 0.0));

			//������x�N�g���̉��Z
			if (jumping < 5)
			{
				jumping += 0.25f;
			}

			//�J�E���g�̏���
			m_jump_cnt++;
		}
		//�J�E���g���Q�O�t���[����������
		else
		{
			//���ɍ~��Ă���<----
			m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec + Vector3(0.0, jumping, 0.0));
			//�������x�N�g���̌��Z
			jumping -= 0.25f;
			//�n�ʂɒ�������
			if (jumping < 0.0f)
			{
				//�t���O��OFF�ɂ���
				m_jump = false;
				//�J�E���g�̏�����
				m_jump_cnt = 0;
				//�x�N�g���̏������i�O�̂��߁j
				jumping = 0;
			}
		}

	}
	//A�L�[�������ꂽ��
	if (key.A)
	{
		LeftRotation();
		//float angle = m_ObjPlayer[0].Get_rotate().y;
		//m_ObjPlayer[0].Set_rotate(Vector3(0, angle + 0.01f, 0));
	}
	//D�L�[�������ꂽ��
	if (key.D)
	{
		RightRotation();
		//float angle = m_ObjPlayer[0].Get_rotate().y;
		//m_ObjPlayer[0].Set_rotate(Vector3(0, angle - 0.01f, 0));
	}
	//W�L�[�������ꂽ��
	if (key.W)
	{
		Advance();
		//Vector3 moveV(0, 0, -0.1f);
		//float angle = m_ObjPlayer[0].Get_rotate().y;

		//Matrix rotmat = Matrix::CreateRotationY(angle);
		//moveV = Vector3::TransformNormal(moveV, rotmat);

		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[0].Set_trans(pos + moveV);
	}
	//S�L�[�������ꂽ��
	if (key.S)
	{
		Back();
		//Vector3 moveV(0, 0, 0.1f);
		//float angle = m_ObjPlayer[0].Get_rotate().y;

		//Matrix rotmat = Matrix::CreateRotationY(angle);
		//moveV = Vector3::TransformNormal(moveV, rotmat);

		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[0].Set_trans(pos + moveV);
	}

	//Z�L�[�������ꂽ��i�U�����[�V�����j
	if (key.Z)
	{
		Attack();

		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos + Vector3(0.5, 0.5, -1.0));
	}
	//X�L�[�������ꂽ��i�h�䃂�[�V�����j
	if (key.X)
	{
		Defence();
	}
	//V�L�[�������ꂽ��i�W�����v���[�V�����j
	if (key.V)
	{
		Jump();
		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos + Vector3(0.5, 0.5, -1.0));
	}

	//�X�y�[�X�L�[�������ꂽ��i�e�ہj
	if (keyTracker->pressed.Space)
	{
		//�������˒��Ȃ�
		if (m_FireFlag)
		{
			//�p�[�c�̈ʒu���Z�b�g
       		ResetBullet();
		}
		else if(!m_FireFlag)
		{
			//���˂���
			FireBullet();
		}

	}



	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	//�����蔻��̍X�V
	m_collisionNodeBullet.Update();

	//�e�ۂ�O�i
	if(m_FireFlag)
	{
		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_WEAPON].Get_transmat();
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos + m_BulletVel);
	}



	//FireBullet();


}

void Player::Render()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Draw();
	}
	//�����蔻��̕`��
	m_collisionNodeBullet.Draw();


}

//��----------------------------------------------------��
//��*func�F�U�����[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Attack()
{
	if (!m_defense && !m_jump)
	{
		m_attack = true;
	}
}

//��----------------------------------------------------��
//��*func�F�h�䃂�[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Defence()
{
	if (!m_attack && !m_jump)
	{
		m_defense = true;
	}
}

//��----------------------------------------------------��
//��*func�F�W�����v���[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Jump()
{
	if (!m_attack && !m_defense)
	{
		m_jump = true;
	}
}

//��----------------------------------------------------��
//��*func�F�O�i
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Advance()
{
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);
}

//��----------------------------------------------------��
//��*func�F��i
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::Back()
{
	Vector3 moveV(0, 0, 0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//��----------------------------------------------------��
//��*func�F����]
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::LeftRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(0, angle + 0.01f, 0));
}

//��----------------------------------------------------��
//��*func�F�E��]
//��*arg�F�e�I�u�W�F�N�g
//��*return�F�Ȃ�
//��----------------------------------------------------��
void Player::RightRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(0, angle - 0.01f, 0));
}

DirectX::SimpleMath::Vector3 Player::Get_scale()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_scale();
}

float Player::Get_rotate()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
}

DirectX::SimpleMath::Vector3 Player::Get_transmat()
{
	return m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
}

void Player::FireBullet()
{
	//���łɔ��˒�
	if (m_FireFlag)
	{
		return;
	}
	//�e�q�֌W�������������[���h���W���擾
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_WEAPON].Get_world();

	Vector3 scale;
	Quaternion rotq;
	Vector3 pos;

	worldm.Decompose(scale, rotq, pos);

	////�s��̂P�s����Vector3�Ƃ��Ĉ���
	//Vector3* m0 = (Vector3*)&worldm.m[0];
	//Vector3* m1 = (Vector3*)&worldm.m[1];
	//Vector3* m2 = (Vector3*)&worldm.m[2];
	//Vector3* m3 = (Vector3*)&worldm.m[3];

	////���[���h���W�����o��
	//pos = *m3;

	////���[���h�X�P�[�����O�����o��
	//scale = Vector3(m0->Length(), m1->Length(), m2->Length());

	////�X�P�[�����O��ł�����
	//m0->Normalize();
	//m1->Normalize();
	//m2->Normalize();

	////���[���h��]�����o��
	//rotq = Quaternion::CreateFromRotationMatrix(worldm);

	//�e�q�֌W������
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_perant(nullptr);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_scale(scale);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotateQ(rotq);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos);

	//�e�ۂ̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotq);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	//���˒��ł͂Ȃ�
	if (!m_FireFlag)
	{
		return;
	}
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_scale(Vector3(1, 1, 1));
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotate(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));

	m_FireFlag = false;
}

