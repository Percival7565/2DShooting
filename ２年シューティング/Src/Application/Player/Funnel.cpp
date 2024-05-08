#include "../Scene/Scene.h"
#include "Funnel.h"


void C_Funnel::Init()
{
	m_Tex.Load("Texture/Funnel/demo_funnel.png");
}

void C_Funnel::Update()
{
	m_mat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void C_Funnel::Draw()
{
	DrawImg(m_mat,&m_Tex,{0,0,32,32},1.0f);
}
