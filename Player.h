#pragma once
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include "Camera.h"
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"


class Player 
{
public:
	//自機パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_DOWNBODY,
		PLAYER_PARTS_WEAPON,

		PLAYER_PARTS_NUM
	};

	Player(DirectX::Keyboard* keyboard);
	~Player();

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

	//任意のパーツを発射
	void FireBullet();

	//パーツを取り付けなおす
	void ResetBullet();


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

	std::vector<Obj3d> m_ObjPlayer;

	//キーボード
	DirectX::Keyboard* keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker;


	//弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel;

	//弾丸が発射中かどうか
	bool m_FireFlag;

};

