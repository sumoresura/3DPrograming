#pragma once

class Earth;

class Moon :public KdGameObject
{
public:
	Moon() {};
	~Moon()override {};

	void Update()override;
	void DrawLit()override;
	void Init()override;

	void SetEarth(Earth* _earth) { m_earth = m_earth; }

private:
	std::shared_ptr<KdModelData>m_model = nullptr;

	float m_yRot = 0.0f;
	float m_yRotPow = 1.0f;

	Earth* m_earth;
};