#include "../Scene/Scene.h"
#include "Ability.h"

void C_Ability::Init()
{
	m_abiATex.Load("Texture/Ability/abi_A.png");
	m_abiBTex.Load("Texture/Ability/abi_B.png");
	m_abiCTex.Load("Texture/Ability/abi_C.png");
	m_abiDTex.Load("Texture/Ability/abi_D.png");
	m_abiETex.Load("Texture/Ability/abi_E.png");
	m_pos = {0,-200};
	m_sc = {1,1};
	m_abiAalpha = 0.0f;
	m_rollspead = 20.0f;
	m_rollstopFlg = false;
	m_SelectAbi = 0;
	m_GetAbi = 0;
}

void C_Ability::Update()
{
	m_pos.y -= m_rollspead;
	
	if (m_pos.y < -250)
	{
		m_pos.y = 250;
		m_abiAalpha = 0.0f;
		SelectAbility();
	}
	

	if (m_pos.y > 0)
	{
		m_abiAalpha += 0.08f;
		if (m_abiAalpha == 1.0f)
		{
			m_abiAalpha = 1.0f;
		}
	}
	else
	{
		if (!m_rollstopFlg)
		{
			m_abiAalpha -= 0.08f;
		}
	}
	
	//デバッグ
	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (m_pos.y > 200)
		{
			m_rollstopFlg = true;
			//Stop();
		}
	}
	else
	{
		m_GetAbi = 0;
	}

	if (m_rollstopFlg)
	{
		if (m_rollspead >= 1.0f)
		{
			m_rollspead -= 1.0f;
			if (m_rollspead <= 1.0f&&m_pos.y < 10&&m_pos.y > -10)
			{
				//m_player.SetAbility(1);
				m_pos.y = 0;
				m_rollspead = 1.0f;
				//m_player.SetAbility(m_SelectAbi);
				m_GetAbi = m_SelectAbi;

				//m_SelectAbi = 0;
				//m_GetAbi = 0;
			}
		}
		else
		{
			m_rollspead = 1.0f;
		}
	}

	//デバッグ
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_pos = { 0,-200 };
		m_sc = { 1,1 };
		m_abiAalpha = 0.0f;
		m_rollspead = 20.0f;
		m_rollstopFlg = false;
		m_GetAbi = 0;
	}

	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_smat = Math::Matrix::CreateScale(m_sc.x, m_sc.y, 0);
	m_mat = m_smat * m_tmat;
}

void C_Ability::Draw()
{
	switch (m_SelectAbi)
	{
	case 0:
		
		break;
	case 1:
		DrawImg(m_mat, &m_abiATex, { 0,0,128,128 }, m_abiAalpha);
		break;
	case 2:
		DrawImg(m_mat, &m_abiBTex, { 0,0,128,128 }, m_abiAalpha);
		break;
	case 3:
		DrawImg(m_mat, &m_abiCTex, { 0,0,128,128 }, m_abiAalpha);
		break;
	case 4:
		DrawImg(m_mat, &m_abiDTex, { 0,0,128,128 }, m_abiAalpha);
		break;
	case 5:
		DrawImg(m_mat, &m_abiETex, { 0,0,128,128 }, m_abiAalpha);
		break;
	default:
		break;
	}
	
}

void C_Ability::SelectAbility()
{
	m_SelectAbi = rand() % 5 + 1;
}

void C_Ability::Stop()
{
	//if (m_rollspead >= 1.0f)
	//{
	//	m_rollspead -= 1.0f;
	//	if (m_rollspead <= 1.0f && m_pos.y < 10 && m_pos.y > -10)
	//	{
	//		m_pos.y = 0;
	//		m_rollspead = 0.0f;
	//		//m_player.SetAbility(m_SelectAbi);
	//		m_GetAbi = m_SelectAbi;

	//		//m_SelectAbi = 0;
	//		//m_GetAbi = 0;
	//	}
	//}
	//else
	//{
	//	m_rollspead = 1.0f;
	//}
}
