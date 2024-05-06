#include "../Scene/Scene.h"
#include "Wave.h"

void C_Wave::Init()
{
	m_waveTex.Load("Texture/UI/wave.png");
	m_pos = {90,0};
	m_sc = {0,0};
	m_waveAlpha = 1.0f;
	m_addPos = 0.0f;

	m_numPos = {90,0};
}

void C_Wave::Update()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_sc.x += 0.1f;
		m_sc.y += 0.1f;
		m_pos.x -= 5;

		//m_numPos.x += 7;
		m_addPos += 5;

		m_waveAlpha -= 0.008f;
		//m_waveAlpha -= 0.01f;

		NumAlpha = m_waveAlpha;
	}

	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_smat = Math::Matrix::CreateScale(m_sc.x, m_sc.y, 0);
	m_mat = m_smat * m_tmat;
}

void C_Wave::Draw()
{
	DrawImg(m_mat, &m_waveTex, { 0,0,150,50 }, m_waveAlpha);
	m_number.DrawWaveNum(9, { m_numPos.x  ,m_numPos.y }, NumAlpha, { m_sc.x ,m_sc.y  },m_addPos);
}
