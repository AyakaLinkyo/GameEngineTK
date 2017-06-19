#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


void CollisionNode::SetParent(Obj3d * parent)
{
	m_obj.Set_perant(parent);
}


SphereNode::SphereNode()
{
	//デフォルト半径を１メートルにする
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	SphereNode();
	//デバック表示用モデルを読み込む
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.Set_trans(m_trans);
	m_obj.Set_scale(Vector3(m_LocalRadius));
	m_obj.Update();
}

void SphereNode::Draw()
{
	m_obj.Draw();
}

