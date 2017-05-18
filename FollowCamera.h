//∞----------------------------------------------------∞
//∞*ファイル名：FollowCamera.h							∞
//∞*内容　　　：自機に追従するカメラクラス				∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.15								∞
//∞----------------------------------------------------∞

#pragma once
#include "Camera.h"
class FollowCamera :
	public Camera
{
public:
	//自機とカメラの距離
	static const float CAMERA_DISTANCE;	
	//コンストラクタ
	FollowCamera(int width, int height);
	//毎フレーム更新
	void Update() override;

	//追従対象の座標をセット
	void Set_target_pos(const DirectX::SimpleMath::Vector3& target_pos);
	//追従対象の角度をセット
	void Set_target_rotate(float target_rotate);


protected:
	//追従対象の座標
	DirectX::SimpleMath::Vector3 m_target_pos;
	//追従対象の回転角
	float m_target_rotate;

};

