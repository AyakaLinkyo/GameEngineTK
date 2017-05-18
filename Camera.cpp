//∞----------------------------------------------------∞
//∞*ファイル名：Camera.h								∞
//∞*内容　　　：カメラを制御するクラス					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.11								∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Camera.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


//∞----------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞*return：なし
//∞----------------------------------------------------∞
Camera::Camera(int width, int height)
{
	//メンバ変数の初期化
	//ビュー行列
	//どこから見るのか（視点）
	eyepos = Vector3(0, 0, 5);
	//どこを見るのか（注視点/参照点）
	refpos = Vector3(0, 0, 10);
	//どちらが画面上方向か（上方向ベクトル）
	upvec = Vector3(0, 1, 0);
	//ベクトルの正規化（長さを１にする）
	upvec.Normalize();

	//プロジェクション行列
	//垂直方向視野角
	fovY = XMConvertToRadians(60.0f);
	//アスペクト比（横と縦の比率）
	aspect = (float)width / height;
	//手前の表示限界距離
	nearclip = 0.1f;
	//奥の表示限界距離
	farclip = 1000.0f;

	//ビュー行列を作成
	view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	//射影行列の生成（透視投影用）
	proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

}


Camera::~Camera()
{
}

void Camera::Update()
{
	//ビュー行列を作成
	view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	//射影行列の生成（透視投影用）
	proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

}

const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{	
	////ビュー行列を作成
	//view = Matrix::CreateLookAt(eyepos, refpos, upvec);

	return view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProjMatrix()
{
	////射影行列の生成（透視投影用）
	//proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearclip, farclip);

	return proj;
}

void Camera::SetEyepos(const DirectX::SimpleMath::Vector3& eyepos)
{
	this->eyepos = eyepos;
}

void Camera::SetRefpos(const DirectX::SimpleMath::Vector3 & refpos)
{
	this->refpos = refpos;
}

void Camera::SetUppos(const DirectX::SimpleMath::Vector3 & uppos)
{
	this->upvec = uppos;
}

void Camera::SetForY(float fovY)
{
	this->fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	this->aspect = aspect;
}

void Camera::SetNearClip(float nearclip)
{
	this->nearclip = nearclip;
}

void Camera::SetFarClip(float farclip)
{
	this->farclip = farclip;
}
