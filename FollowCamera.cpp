
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
	m_keyboard = nullptr;
	camera_flag = true;
}

void FollowCamera::Update()
{
	//キーボードの情報取得
	Keyboard::State keyboard_state = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboard_state);

	//Cを押すたびにFPS/TPSを入れ替える
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		//フラグの切り替え
		if (camera_flag)
		{
			camera_flag = false;
		}
		else
		{
			camera_flag = true;
		}
	}

	//視点、参照点
	Vector3 eyepos, refpos;

	if(camera_flag)
	{
		//TPSカメラ処理
		//ターゲットの座標は自機の座標に追従
		refpos = m_target_pos + Vector3(0, 2.0f, 0);
		//ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	
		//カメラの視線方向の逆方向に回転
		Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
	
		//視点座標を計算
		eyepos = refpos + cameraV;
		//視点を現在位置から補間する
		//次の視点＝今の視点+(次の視点-今の視点)*補間割合
		eyepos = Camera::eyepos + (eyepos - Camera::eyepos) * 0.05f;
	
		//参照点を現在位置から補間する
		refpos = Camera::refpos + (refpos - Camera::refpos) * 0.2f;
	}

	else
	{//FPSカメラ
	//自機の目の位置あたりを視点とする
		Vector3 position;
		position = m_target_pos + Vector3(0, 0.2f, 0);
		//eyepos = m_target_pos + Vector3(0, 0.2f, 0);
		//ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
		//カメラの視線方向の逆方向に回転
		Matrix rotmat = Matrix::CreateRotationY(m_target_rotate);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV*0.1f;

		//参照点座標を計算
		refpos = position + cameraV;

	}


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

void FollowCamera::Set_keyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
