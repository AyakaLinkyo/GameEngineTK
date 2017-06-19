#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//∞----------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞----------------------------------------------------∞
Player::Player(DirectX::Keyboard* keyboard)
{
	//自機パーツの読み込み
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].LoadModel(L"Resources/down_body.cmo");
	m_ObjPlayer[PLAYER_PARTS_WEAPON].LoadModel(L"Resources/weapon.cmo");


	//パーツの親子関係をセット
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	m_ObjPlayer[PLAYER_PARTS_HEAD].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_perant(&m_ObjPlayer[PLAYER_PARTS_BODY]);

	//親からのオフセット
	//m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(Vector3(0, 0.35, 0));
	m_ObjPlayer[PLAYER_PARTS_HEAD].Set_trans(Vector3(0, 1.5, 0));
	m_ObjPlayer[PLAYER_PARTS_DOWNBODY].Set_trans(Vector3(0, 0, 0));
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));

	//*----------------------------------------------------------------------*//
	//それぞれのモーションに使用するフラグ、カウントの初期化

	m_attack = false;		//攻撃フラグ
	m_attack_cnt = 0;		//攻撃カウント

	m_defense = false;		//防御フラグ
	m_defense_cnt = 0;		//防御カウント

	m_jump = false;			//ジャンプフラグ
	m_jump_cnt = 0;			//ジャンプカウント
	jumping = 0.0f;			//方向ベクトルの初期化
//*----------------------------------------------------------------------*//


	//きーぼーどの初期化
	this->keyboard = keyboard;
	keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	std::unique_ptr<Keyboard::KeyboardStateTracker> keyTracker(new Keyboard::KeyboardStateTracker);
	//発射中ではない
	m_FireFlag = false;

	//弾丸用の当たり判定を設定
	{
		m_collisionNodeBullet.Initialize();
		//親パーツの指定
		m_collisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_WEAPON]);
		m_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_collisionNodeBullet.SetLocalRadius(1.0f);
	}
}

//∞----------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
Player::~Player()
{
}


void Player::Init()
{
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：武器オブジェクト,親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Update()
{
	//キーボードの情報取得
	Keyboard::State key = keyboard->GetState();
	keyTracker->Update(key);


	//攻撃モーション
	if (m_attack)
	{
		//盾（腕）を前に突き出す
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans((Vector3(0, 0.35, 0)) + Vector3(0.5, 0.5, -1.0));

		//カウント追加
		m_attack_cnt++;

		//２０フレーム後
		if (m_attack_cnt > 20)
		{
			//盾（腕）をもとに戻す
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));
			//フラグをOFFにする
			m_attack = false;
			//カウントの初期化
			m_attack_cnt = 0;
		}

	}

	//防御モーション
	if (m_defense)
	{
		//盾を回転させる（防御姿勢用）
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotate(Vector3(5.0, 2.0, 3.0));
		//盾を前に突き出す
		m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans((Vector3(0, 0.35, 0)) + Vector3(0.5, 0.5, -1.0));

		//カウント処理
		m_defense_cnt++;

		//２０フレーム後
		if (m_defense_cnt > 20)
		{
			//盾の回転をもとに戻す
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotate(Vector3(0.0, 0.0, 0.0));
			//盾の位置を戻す
			m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(Vector3(0.5, 0.5, 0));
			//フラグの初期化
			m_defense = false;
			//カウントの初期化
			m_defense_cnt = 0;
		}

	}
	//ジャンプモーション
	if (m_jump)
	{
		if (m_jump_cnt == 0)
		{
			vec = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
		}
		//カウントが２０フレーム以下の場合
		if (m_jump_cnt < 20)
		{
			//上にジャンプする
			m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec + Vector3(0.0, jumping, 0.0));

			//上方向ベクトルの加算
			if (jumping < 5)
			{
				jumping += 0.25f;
			}

			//カウントの処理
			m_jump_cnt++;
		}
		//カウントが２０フレーム超えたら
		else
		{
			//下に降りてくる<----
			m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(vec + Vector3(0.0, jumping, 0.0));
			//下方向ベクトルの減算
			jumping -= 0.25f;
			//地面に着いたら
			if (jumping < 0.0f)
			{
				//フラグをOFFにする
				m_jump = false;
				//カウントの初期化
				m_jump_cnt = 0;
				//ベクトルの初期化（念のため）
				jumping = 0;
			}
		}

	}
	//Aキーが押されたら
	if (key.A)
	{
		LeftRotation();
		//float angle = m_ObjPlayer[0].Get_rotate().y;
		//m_ObjPlayer[0].Set_rotate(Vector3(0, angle + 0.01f, 0));
	}
	//Dキーが押されたら
	if (key.D)
	{
		RightRotation();
		//float angle = m_ObjPlayer[0].Get_rotate().y;
		//m_ObjPlayer[0].Set_rotate(Vector3(0, angle - 0.01f, 0));
	}
	//Wキーが押されたら
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
	//Sキーが押されたら
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

	//Zキーが押されたら（攻撃モーション）
	if (key.Z)
	{
		Attack();

		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos + Vector3(0.5, 0.5, -1.0));
	}
	//Xキーが押されたら（防御モーション）
	if (key.X)
	{
		Defence();
	}
	//Vキーが押されたら（ジャンプモーション）
	if (key.V)
	{
		Jump();
		//Vector3 pos = m_ObjPlayer[0].Get_transmat();
		//m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos + Vector3(0.5, 0.5, -1.0));
	}

	//スペースキーが押されたら（弾丸）
	if (keyTracker->pressed.Space)
	{
		//もし発射中なら
		if (m_FireFlag)
		{
			//パーツの位置リセット
       		ResetBullet();
		}
		else if(!m_FireFlag)
		{
			//発射する
			FireBullet();
		}

	}



	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin(); it != m_ObjPlayer.end(); it++)
	{
		it->Update();
	}

	//当たり判定の更新
	m_collisionNodeBullet.Update();

	//弾丸を前進
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
	//当たり判定の描画
	m_collisionNodeBullet.Draw();


}

//∞----------------------------------------------------∞
//∞*func：攻撃モーション
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Attack()
{
	if (!m_defense && !m_jump)
	{
		m_attack = true;
	}
}

//∞----------------------------------------------------∞
//∞*func：防御モーション
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Defence()
{
	if (!m_attack && !m_jump)
	{
		m_defense = true;
	}
}

//∞----------------------------------------------------∞
//∞*func：ジャンプモーション
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Jump()
{
	if (!m_attack && !m_defense)
	{
		m_jump = true;
	}
}

//∞----------------------------------------------------∞
//∞*func：前進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Advance()
{
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);
}

//∞----------------------------------------------------∞
//∞*func：後進
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::Back()
{
	Vector3 moveV(0, 0, 0.1f);
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;

	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	Vector3 pos = m_ObjPlayer[PLAYER_PARTS_BODY].Get_transmat();
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_trans(pos + moveV);

}

//∞----------------------------------------------------∞
//∞*func：左回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
void Player::LeftRotation()
{
	float angle = m_ObjPlayer[PLAYER_PARTS_BODY].Get_rotate().y;
	m_ObjPlayer[PLAYER_PARTS_BODY].Set_rotate(Vector3(0, angle + 0.01f, 0));
}

//∞----------------------------------------------------∞
//∞*func：右回転
//∞*arg：親オブジェクト
//∞*return：なし
//∞----------------------------------------------------∞
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
	//すでに発射中
	if (m_FireFlag)
	{
		return;
	}
	//親子関係を加味したワールド座標を取得
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_WEAPON].Get_world();

	Vector3 scale;
	Quaternion rotq;
	Vector3 pos;

	worldm.Decompose(scale, rotq, pos);

	////行列の１行ずつをVector3として扱う
	//Vector3* m0 = (Vector3*)&worldm.m[0];
	//Vector3* m1 = (Vector3*)&worldm.m[1];
	//Vector3* m2 = (Vector3*)&worldm.m[2];
	//Vector3* m3 = (Vector3*)&worldm.m[3];

	////ワールド座標を取り出す
	//pos = *m3;

	////ワールドスケーリングを取り出す
	//scale = Vector3(m0->Length(), m1->Length(), m2->Length());

	////スケーリングを打ち消す
	//m0->Normalize();
	//m1->Normalize();
	//m2->Normalize();

	////ワールド回転を取り出す
	//rotq = Quaternion::CreateFromRotationMatrix(worldm);

	//親子関係を解除
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_perant(nullptr);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_scale(scale);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_rotateQ(rotq);
	m_ObjPlayer[PLAYER_PARTS_WEAPON].Set_trans(pos);

	//弾丸の速度を設定
	m_BulletVel = Vector3(0, 0, -0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotq);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	//発射中ではない
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

