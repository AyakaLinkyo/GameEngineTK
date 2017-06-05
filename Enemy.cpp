#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//∞----------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞----------------------------------------------------∞
ENEMY::ENEMY()
{
	//自機パーツの読み込み
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].LoadModel(L"Resources/down_body.cmo");
	m_ObjEnemy[ENEMY_PARTS_WEAPON].LoadModel(L"Resources/weapon.cmo");


	//パーツの親子関係をセット
	m_ObjEnemy[ENEMY_PARTS_HEAD].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);

	m_ObjEnemy[ENEMY_PARTS_WEAPON].Set_perant(&m_ObjEnemy[ENEMY_PARTS_BODY]);

	vec = Vector3(rand() % 100 + 1, 0, rand() % 100 + 1);

	//親からのオフセット
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(vec);
	m_ObjEnemy[ENEMY_PARTS_HEAD].Set_trans(Vector3(0, 1.5, 0));
	m_ObjEnemy[ENEMY_PARTS_DOWNBODY].Set_trans(Vector3(0, 0, 0));
	m_ObjEnemy[ENEMY_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));

	////きーぼーどの初期化
	//this->keyboard = keyboard;


	m_timer = 0;
	m_DistAngle = 0;
}

//∞----------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
ENEMY::~ENEMY()
{
}


void ENEMY::Init()
{
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：武器オブジェクト,親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void ENEMY::Update()
{
	//定期的に進行方向を変える
	m_timer--;
	if (m_timer < 0)
	{
		m_timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;
		m_DistAngle += rnd;
	}

	//目標角度に向かって、機体の角度をじわじわ補間
	{
		Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate();

		//目標角度への、最短角度を取得
		float angle = GetShortAngleRad(rotv.y, XMConvertToRadians(m_DistAngle));
		rotv.y += angle*0.01f;
		m_ObjEnemy[ENEMY_PARTS_BODY].Set_rotate(rotv);
	}
	//機体の向いている方向に進む
	{
		//今の座標を取得
		Vector3 trans = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();

		Vector3 move(0, 0, -0.02f);
		Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate();
		Matrix rotm = Matrix::CreateRotationY(rotv.y);
		move = Vector3::TransformNormal(move, rotm);

		//座標を移動
		trans += move;
		//移動後の座標をセット
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
//∞----------------------------------------------------∞
//∞*func：前進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void ENEMY::Advance()
{
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(pos + moveV);
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void ENEMY::Back()
{
	Vector3 moveV(0, 0, 0.1f);
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjEnemy[ENEMY_PARTS_BODY].Get_transmat();
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：左回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void ENEMY::LeftRotation()
{
	float angle = m_ObjEnemy[ENEMY_PARTS_BODY].Get_rotate().y;
	m_ObjEnemy[ENEMY_PARTS_BODY].Set_rotate(Vector3(0, angle + 0.01f, 0));
}

//∞----------------------------------------------------∞
//∞*func：右回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
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

