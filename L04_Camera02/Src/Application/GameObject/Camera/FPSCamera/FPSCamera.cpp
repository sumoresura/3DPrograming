#include"FPSCamera.h"

void FPSCamera::Init()
{
	// 基準点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.f);

	// ↓画面中央の座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 320;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void FPSCamera::Update()
{
	// ターゲットの行列
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>
		_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();

	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;
	//					ローカル			ワールド
	CameraBase::Update();
}