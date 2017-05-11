//∞----------------------------------------------------∞
//∞*ファイル名：Camera.h								∞
//∞*内容　　　：カメラクラスのヘッダー					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.11								∞
//∞----------------------------------------------------∞

#pragma once
#include <SimpleMath.h>



class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	//更新
	void Update();

	//ビュー行列を取得する関数
	DirectX::SimpleMath::Matrix GetViewMatrix();
	//射影行列を取得する関数
	DirectX::SimpleMath::Matrix GetProjMatrix();
	//視点をセット
	void SetEyepos(DirectX::SimpleMath::Vector3 eyepos);

protected:
	//ビュー行列
	DirectX::SimpleMath::Matrix view;
	//どこから見るのか（視点）
	DirectX::SimpleMath::Vector3 eyepos;
	//どこを見るのか（注視点/参照点）
	DirectX::SimpleMath::Vector3 refpos;
	//どちらが画面上方向か（上方向ベクトル）
	DirectX::SimpleMath::Vector3 upvec;


	//プロジェクション行列
	DirectX::SimpleMath::Matrix proj;

	//垂直方向視野角
	float fovY;
	//アスペクト比（横と縦の比率）
	float aspect;
	//手前の表示限界距離
	float nearclip;
	//奥の表示限界距離
	float farclip;

};

