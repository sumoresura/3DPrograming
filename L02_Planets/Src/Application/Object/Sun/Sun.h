#pragma once

class Sun :public KdGameObject
{
public:
	Sun() {};
	~Sun()override {};

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData>m_model = nullptr;

	float m_yRot = 0.0f;
	float m_yRotPow = 1.0f;
};