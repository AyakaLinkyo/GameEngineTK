
//当たり判定ノード

#pragma once
#include "Collision.h"
#include "Obj3d.h"

//当たり判定ノード（基底クラス）
class CollisionNode
{
public:
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() = 0;
	//親をセットする関数
	void SetParent(Obj3d* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_trans = trans;
	}

protected:
	//デバック表示用オブジェクト
	Obj3d m_obj;
	//親からのオフセット
	DirectX::SimpleMath::Vector3 m_trans;
};

//球の当たり判定ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	void SetLocalRadius(float radius)
	{
		m_LocalRadius = radius;
	}
protected:
	//ローカル半径
	float m_LocalRadius;
};