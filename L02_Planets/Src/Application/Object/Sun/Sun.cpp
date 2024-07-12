#include "Sun.h"

void Sun::Update()
{
	m_yRot += m_yRotPow;
	Math::Matrix rotMat;
	rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_yRot));
	m_mWorld = rotMat;
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}

void Sun::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/sun.gltf");
}
