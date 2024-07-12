#include "Character.h"
#include "../../main.h"
#include "../../GameObject/Camera/CameraBase.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		moveVec = moveVec.TransformNormal(moveVec, _spCamera->GetRotationYMatrix());
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターの回転角度を求める
	UpdateRotate(moveVec);

	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_WorldRot.y));
	m_mWorld = _rotMat* Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::UpdateRotate(const Math::Vector3& srcMoveVec)
{
	//何も入力が無い場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.f)return;

	//キャラの正面方向ベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();

	//移動方向のベクトル
	Math::Vector3 _targetDir = srcMoveVec;
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _TargetAng = atan2(_targetDir.x, _targetDir.z);
	_TargetAng = DirectX::XMConvertToDegrees(_TargetAng);

	//角度の差分を求める
	float _betweenAng = _TargetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}
	else if (_betweenAng < -180)
	{
		_betweenAng += 360;
	}
	float _rotateAng = std::clamp(_betweenAng, -8.f, 8.f);
	m_WorldRot.y += _rotateAng;
}

