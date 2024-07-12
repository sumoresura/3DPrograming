#include "Earth.h"

void Earth::Update()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(4.0f, 0.0f, 0.0f);
	m_yRot += m_yRotPow;
	Math::Matrix rotMat=Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_yRot));
	m_mWorld = rotMat*transMat*rotMat;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Earth::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/earth.gltf");
}
