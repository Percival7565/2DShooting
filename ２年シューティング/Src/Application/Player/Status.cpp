#include "../Scene/Scene.h"
#include "Status.h"

void C_Status::Init()
{
	m_stTex.Load("Texture/UI/status.png");
	m_pos = { 0,0 };
	m_bFlg = false;
}

void C_Status::Update()
{
	//デバッグ
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		m_bFlg = true;
	}
	else
	{
		m_bFlg = false;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Status::Draw()
{
	if (m_bFlg)
	{
		DrawImg(m_mat, &m_stTex, { 0,0,1280,720 }, 0.5f);
	}
}
