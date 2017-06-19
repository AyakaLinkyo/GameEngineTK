
#include <vector>
#include "Obj3d.h"
#include "FollowCamera.h"

#include "CollisionNode.h"



class ENEMY
{
public:
	//自機パーツ
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

	//スケーリング（XYZ)
	DirectX::SimpleMath::Vector3 Get_scale();
	//回転角(XYZ）
	float Get_rotate();
	//平行移動（XYZ）
	DirectX::SimpleMath::Vector3 Get_transmat();

	float GetShortAngleRad(float now_rot, float target_rot);


	const SphereNode& GetcollisionNodeBullet()
	{
		return m_collisionNodeBullet;
	}

private:
	bool m_attack;			//攻撃フラグ
	int m_attack_cnt;		//攻撃カウント

	bool m_defense;			//防御フラグ
	int m_defense_cnt;		//防御カウント

	bool m_jump;			//ジャンプフラグ
	int m_jump_cnt;			//ジャンプカウント
	float jumping;			//方向ベクトルの初期化
	DirectX::SimpleMath::Vector3 vec;

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	std::vector<Obj3d> m_ObjEnemy;

	//キーボード
	DirectX::Keyboard* keyboard;

	int m_timer;
	float m_DistAngle;

	//弾丸用の当たり判定
	SphereNode m_collisionNodeBullet;


};

