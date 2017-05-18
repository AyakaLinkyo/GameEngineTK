
#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;	

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_rotate = 0.0f;
}

void FollowCamera::Update()
{
	//視点、参照点
	Vector3 eyepos, refpos;

	//ターゲットの座標は自機の座標に追従
	refpos = m_target_pos + Vector3(0, 2.0f, 0);
	//ターゲット座標からカメラ座標への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	//カメラの視線方向の逆方向に回転
	Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	//視点座標を計算
	eyepos = refpos + cameraV;

	//カメラに情報セット
	SetEyepos(eyepos);
	SetRefpos(refpos);

	//基底クラスの更新
	Camera::Update();

}

void FollowCamera::Set_target_pos(const DirectX::SimpleMath::Vector3 & target_pos)
{
	this->m_target_pos = target_pos;
}

void FollowCamera::Set_target_rotate(float target_rotate)
{
	this->m_target_rotate = target_rotate;
}
