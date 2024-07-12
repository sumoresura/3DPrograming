#include"CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::Update()
{
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera)return;
	// カメラ情報をセット
	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	// マウスカーソルの差分を求める
	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	// マウスカーソルを再度中央へ固定
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 差分をもとにカメラの回転角度を求める
	m_DegAng.x += mouseMove.y * 0.05f;
	m_DegAng.y += mouseMove.x * 0.05f;
}
