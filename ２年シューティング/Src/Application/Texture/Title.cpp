#include "../Scene/Scene.h"
#include "Title.h"

void C_Title::Init()
{
	m_neonATex.Load("Texture/Title/neonA.png");
	m_neonBTex.Load("Texture/Title/neonB.png");
	//m_neonCTex.Load("Texture/Title/neonC.png");

	m_neonAPos = {0,150};
	m_neonBPos = {0,150};
	//m_neonCPos = {0,150};

	frame = 0;
	m_neonTake = 0;
	m_angle = 0;
	m_Aalpha = 0.0f;
}

void C_Title::Update()
{
	
	switch (m_neonTake)
	{
	case 0:
		m_Aalpha += 0.01f;
		if (m_Aalpha >= 1.0f)
		{
			m_Aalpha = 1.0f;
			m_neonTake = 1;
		}
		break;
	case 1:
		m_angle += 1.0f;
		if (m_angle >= 360.0f)
		{
			m_angle = 0.0f;
		}

		m_Aalpha = 1.0f;
		
		if (rand() % 100 == 0)
		{
			m_neonTake = 2;
		}
		break;

	case 2:
		frame++;
		if (frame >= 10)
		{
			m_Balpha = rand() % 7 * 0.1f;
			frame = 0;
		}

		if (rand() % 100 <= 80)
		{
			m_neonTake = 1;
		}
		

	}

	m_neonAMat = Math::Matrix::CreateTranslation(m_neonAPos.x, m_neonAPos.y, 0);
	m_neonBMat = Math::Matrix::CreateTranslation(m_neonBPos.x, m_neonBPos.y, 0);
	//m_neonCMat = Math::Matrix::CreateTranslation(m_neonCPos.x, m_neonCPos.y, 0);
}

void C_Title::Draw()
{
	

	switch (m_neonTake)
	{
	case 0:
		DrawImg(m_neonAMat, &m_neonATex, { 0,0,640,360 }, m_Aalpha);
		break;
	case 1:
		DrawImg(m_neonAMat, &m_neonATex, { 0,0,640,360 }, m_Aalpha);
		DrawImg(m_neonBMat, &m_neonBTex, { 0,0,640,360 }, sin(DirectX::XMConvertToRadians(m_angle)) * 0.5f);
		break;
	case 2:
		DrawImg(m_neonAMat, &m_neonATex, { 0,0,640,360 }, m_Aalpha);
		DrawImg(m_neonBMat, &m_neonBTex, { 0,0,640,360 }, m_Balpha);
		break;
	/*case 3:
		DrawImg(m_neonAMat, &m_neonATex, { 0,0,640,360 }, m_Aalpha);
		DrawImg(m_neonCMat, &m_neonCTex, { 0,0,640,360 }, 1.0f);
		break;
	case 4:
		DrawImg(m_neonCMat, &m_neonCTex, { 0,0,640,360 }, 1.0f);
		break;*/
	default:
		break;
	}
	
}
