#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	//void Set2dPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetCamera(std::shared_ptr<KdCamera> _camera)
	{
		m_wpCam = _camera;
	}

	void SetTerrain(std::shared_ptr<KdGameObject> _terrain)
	{
		m_wpTerrain = _terrain;
	}

	// マウス座標取得関数
	POINT GetMousePos();

private:
	KdTexture								m_tex;
	std::shared_ptr<KdSquarePolygon>		m_spPoly = nullptr;
	Math::Vector3							m_pos;
	std::weak_ptr<KdCamera>					m_wpCam;
	Math::Vector3							m_camPos;
	std::weak_ptr<KdGameObject>				m_wpTerrain;
	POINT									mousePos;
	Math::Vector3							m_TargetPos = Math::Vector3::Zero;
};