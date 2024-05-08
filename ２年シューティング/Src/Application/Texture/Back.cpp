#include "../Scene/Scene.h"
#include "Back.h"

void C_Back::Init()
{
	m_skyTex.Load("Texture/Back/sky.png");
	m_backATex.Load("Texture/Back/backA.png");
	m_backBTex.Load("Texture/Back/backB.png");
	m_blindTex.Load("Texture/Back/blind.png");

	m_skyPos = {};
	m_aPos[0] = {};
	m_bPos[0] = {};
	m_aPos[1] = {-1598,0};
	m_bPos[1] = {-1709,0};
}

void C_Back::Update()
{
	m_skyMat = Math::Matrix::CreateTranslation(m_skyPos.x, m_skyPos.y, 0);


	for (int b = 0; b < m_backNum; b++)
	{
		m_aPos[b].x -= 0.5f;
		m_bPos[b].x -= 2.0f;

		if (m_aPos[b].x <= -1598)
		{
			m_aPos[b].x = 1598;
		}
		
		if (m_bPos[b].x <= -1709)
		{
			m_bPos[b].x = 1709;
		}

		m_aMat[b] = Math::Matrix::CreateTranslation(m_aPos[b].x, m_aPos[b].y, 0);
		m_bMat[b] = Math::Matrix::CreateTranslation(m_bPos[b].x, m_bPos[b].y, 0);
	}
}

void C_Back::Draw()
{
	DrawImg(m_skyMat, &m_skyTex, { 0,0,1320,720 }, 1.0f);

	for (int b = 0; b < m_backNum; b++)
	{
		DrawImg(m_aMat[b], &m_backATex, {0,0,1598,719}, 1.0f);
	}

	for (int b = 0; b < m_backNum; b++)
	{
		DrawImg(m_bMat[b], &m_backBTex, { 0,0,1709,720 }, 1.0f);
	}

	DrawImg(m_skyMat, &m_blindTex, { 0,0,1280,720 }, 0.5f);
}
