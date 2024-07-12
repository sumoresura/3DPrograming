#include"TPSCamera.h"

void TPSCamera::Init()
{
	// 基準点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);

	// ↓画面中央の座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 320;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
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
	//m_mWorld = m_mRotation * m_mLocalPos * _targetMat;
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;

	//めり込み防止の為の座標補正計算！
	//①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo rayInfo;
	//レイの発車メロディーを設定
	rayInfo.m_pos = GetPos();
	//レイの発射方向を設定
	rayInfo.m_dir = Math::Vector3::Down;
	//レイの長さ
	rayInfo.m_range = 1000;
	//レイの当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;
	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1f;
		rayInfo.m_dir = _targetPos - GetPos();
		//レイの長さ
		rayInfo.m_range = rayInfo.m_dir.Length();
		rayInfo.m_dir.Normalize();
	}

	//②HIT対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject>wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> _retRayList;
			spGameObj->Intersects(rayInfo, &_retRayList);

			//③欠課を使って座標を補完する
			//レイに当たったリストから一番近いオブジェクトを検出
			float _maxOverLap = 0;
			Math::Vector3 _hitPos = {};
			bool _hit = false;
			for (auto& ret : _retRayList)
			{
				//レイを遮断し、オーバーした長さが一番長いものを探す
				if (_maxOverLap < ret.m_overlapDistance)
				{
					_maxOverLap = ret.m_overlapDistance;
					_hitPos = ret.m_hitPos;
					_hit = true;
				}
			}
			//何かしらの障害物に当たっている
			if (_hit)
			{
				Math::Vector3 _hoseiPos = _hitPos;
				_hoseiPos += rayInfo.m_dir * 0.4f;
				SetPos(_hoseiPos);
				//_hitPos+= rayInfo.m_dir * 0.4f;
				//SetPos(_hitPos);
			}
		}
	}

	CameraBase::Update();
}
