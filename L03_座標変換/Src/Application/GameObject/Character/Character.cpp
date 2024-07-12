#include "Character.h"
#include"../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_tex.Load("Asset/Textures/arrow.png");
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ①マウス座標を取得
		mousePos = GetMousePos();

		std::shared_ptr<KdCamera> _cam = m_wpCam.lock();

		// 2D座標を3D座標に変換
		if (_cam)
		{
			Math::Vector3 _camPos = _cam->GetCameraMatrix().Translation();
			Math::Vector3 _rayDir = Math::Vector3::Zero;
			float _range = 1000.0f;
			// ②レイの発射方向を求める(_rayDir)
			_cam->GenerateRayInfoFromClientPos(mousePos, _camPos, _rayDir, _range);

			// ③実際にレイを飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3 _endRayPos = _camPos + (_rayDir * _range);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos);

				// 実際の当たり判定の処理
				std::list<KdCollider::CollisionResult>_results;
				_terrain->Intersects(_rayInfo, &_results);

				// 結果が一つでも帰ってきたら
				if (_results.size())
				{
					for (KdCollider::CollisionResult result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}

	}


	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = GetPos();
	Math::Vector3 moveVec = m_TargetPos - nowPos;



	if (moveVec.Length() < moveSpd)
	{
		moveSpd = moveVec.Length();
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);

	/*Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat=Math::Matrix::CreateScale(0.5, 0.5, 0.5);
	m_fontMat = scaleMat;*/
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	// ①ハムスターの3D座標を2D座標に変換する
	std::shared_ptr<KdCamera> _cam = m_wpCam.lock();
	if (_cam)
	{
		_cam->ConvertWorldToScreenDetail(GetPos(), m_pos);
	}
	Math::Color col = { 1,1,1,1 };
	Math::Rectangle rc = { 0,0,221,67 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y + 100, &rc, &col);

	//KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 10, &kRedColor);
}

POINT Character::GetMousePos()
{
	POINT _mousePos;

	GetCursorPos(&_mousePos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

	return _mousePos;
}