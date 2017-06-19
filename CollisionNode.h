
//�����蔻��m�[�h

#pragma once
#include "Collision.h"
#include "Obj3d.h"

//�����蔻��m�[�h�i���N���X�j
class CollisionNode
{
public:
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() = 0;
	//�e���Z�b�g����֐�
	void SetParent(Obj3d* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_trans = trans;
	}

protected:
	//�f�o�b�N�\���p�I�u�W�F�N�g
	Obj3d m_obj;
	//�e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_trans;
};

//���̓����蔻��m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	void SetLocalRadius(float radius)
	{
		m_LocalRadius = radius;
	}
protected:
	//���[�J�����a
	float m_LocalRadius;
};