#pragma once

class Earth :public KdGameObject
{
public:
	Earth() {};
	~Earth()override {};

	void Update()override;
	void DrawLit()override;
	void Init()override;

	Earth* GetOwner() { return this; }

private:
	std::shared_ptr<KdModelData>m_model = nullptr;

	float m_yRot = 0.0f;
	float m_yRotPow = 0.5f;

};