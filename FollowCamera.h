#pragma once

#include "Camera.h"
#include <Keyboard.h>

class FollowCamera :public Camera
{
private:
	static const float CAMERA_DISTANCE;

protected:
	// 追従対象対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;
	// 追従対象の回転角
	float m_targetAngle;

	// キーボード
	DirectX::Keyboard* m_keyboard;
	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	// カメラ切り替えフラグ
	bool m_isChangeFPS;

public:

	FollowCamera(int width, int height);

	virtual ~FollowCamera();

	void Update();

	// 追従対象の座標をセット
	void SetTargetPos(DirectX::SimpleMath::Vector3 targetPos);

	// 追従対象の回転角をセット
	void SetTargetAngle(float targetAngle);

	// キーボードをセット
	void SetKeyboard(DirectX::Keyboard* keyboard);
};