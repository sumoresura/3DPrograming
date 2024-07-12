#include "Moon.h"
#include "../Earth/Earth.h"

void Moon::Update()
{
	//Math::Matrix transMat = Math::Matrix::CreateTranslation((m_earth->GetPos().x)+5.0f, m_earth->GetPos().y, m_earth->GetPos().z);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(5.0f,0, 0);
	m_yRot += m_yRotPow;
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_yRot));
	m_mWorld =transMat*rotMat;
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Moon::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/moon.gltf");
}
