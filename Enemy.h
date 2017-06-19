
#include <vector>
#include "Obj3d.h"
#include "FollowCamera.h"

#include "CollisionNode.h"



class ENEMY
{
public:
	//���@�p�[�c
	enum Enemy_PARTS
	{
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_HEAD,
		ENEMY_PARTS_DOWNBODY,
		ENEMY_PARTS_WEAPON,

		ENEMY_PARTS_NUM
	};

	ENEMY();
	~ENEMY();

	void Init();
	void Update();
	void Render();

	void Attack();
	void Defence();
	void Jump();

	void Advance();
	void Back();
	void LeftRotation();
	void RightRotation();

	//�X�P�[�����O�iXYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//��]�p(XYZ�j
	float Get_rotate();
	//���s�ړ��iXYZ�j
	DirectX::SimpleMath::Vector3 Get_transmat();

	float GetShortAngleRad(float now_rot, float target_rot);


	const SphereNode& GetcollisionNodeBullet()
	{
		return m_collisionNodeBullet;
	}

private:
	bool m_attack;			//�U���t���O
	int m_attack_cnt;		//�U���J�E���g

	bool m_defense;			//�h��t���O
	int m_defense_cnt;		//�h��J�E���g

	bool m_jump;			//�W�����v�t���O
	int m_jump_cnt;			//�W�����v�J�E���g
	float jumping;			//�����x�N�g���̏�����
	DirectX::SimpleMath::Vector3 vec;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	std::vector<Obj3d> m_ObjEnemy;

	//�L�[�{�[�h
	DirectX::Keyboard* keyboard;

	int m_timer;
	float m_DistAngle;

	//�e�ۗp�̓����蔻��
	SphereNode m_collisionNodeBullet;


};

