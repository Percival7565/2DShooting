#include "../Scene/Scene.h"
#include "Ability.h"

void C_Ability::Init()
{
	m_abiATex.Load("Texture/Ability/abi_A.png");
	m_abiBTex.Load("Texture/Ability/abi_B.png");
	m_abiCTex.Load("Texture/Ability/abi_C.png");
	m_abiDTex.Load("Texture/Ability/abi_D.png");
	m_pos = {0,-200};
	m_sc = {1,1};
	m_abiAalpha = 0.0f;
	m_rollspead = 20.0f;
	m_rollstopFlg = false;
	m_SelectAbi = 0;
	m_GetAbi = 0;
	frame = 0;
	frame2 = 0;
	m_DrawCharFlg = false;
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
	frame++;
	frame2++;

	//if (GetAsyncKeyState('R') & 0x8000)
	if (frame>=150)
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
				m_DrawCharFlg = true;
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
	//if (frame >= 310)
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

void C_Ability::ReRoll()
{
	m_pos = { 0,-200 };
	m_sc = { 1,1 };
	m_abiAalpha = 0.0f;
	m_rollspead = 20.0f;
	m_rollstopFlg = false;
	m_GetAbi = 0;
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
	default:
		break;
	}
	
	if (m_DrawCharFlg)
	{
		switch (m_SelectAbi)
		{
		case 0:
			
			break;
		case 1:
			SHADER.m_spriteShader.DrawString(-100, -200, "同時発射球数がプラス１", Math::Vector4(1, 1, 0, 1));
			break;
		case 2:
			SHADER.m_spriteShader.DrawString(-100, -200, "発射する球のサイズ増加", Math::Vector4(1, 1, 0, 1));
			break;
		case 3:
			SHADER.m_spriteShader.DrawString(-150, -200, "自機の発射する連射速度が加速", Math::Vector4(1, 1, 0, 1));
			break;
		case 4:
			SHADER.m_spriteShader.DrawString(-200, -200, "ファンネルを展開（以降重複時は発射速度増加）", Math::Vector4(1, 1, 0, 1));
			break;
		default:
			break;
		}

		SHADER.m_spriteShader.DrawString(400, -300, "Vキーで次WAVE", Math::Vector4(1, 1, 0, (sin(DirectX::XMConvertToRadians(frame2)) * 0.5f) + 0.6f));
	}
}

void C_Ability::SelectAbility()
{
	m_SelectAbi = rand() % 4 + 1;
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
