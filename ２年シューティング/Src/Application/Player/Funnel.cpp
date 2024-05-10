#include "../Scene/Scene.h"
#include "Funnel.h"


void C_Funnel::Init()
{
	frame = 0;
	bulframe = 0;
	animeframe = 0;
	m_pos = {};
	m_Tex.Load("Texture/Funnel/attack_funnel.png");
	m_funnelPause = false;
	m_target = {};
	m_smallest = 0;
	m_smallestNext = 5000.0f;
	m_funnelAnimeCnt = 0;
	m_funnelBulSpeed = 0;
	m_funnelBulFast = 0.0f;
}

void C_Funnel::Update(Math::Vector2 a_pos)
{
	frame++;
	bulframe++;

	m_pos.x = a_pos.x + cos(DirectX::XMConvertToRadians(frame / 2)) * 100;
	m_pos.y = a_pos.y + sin(DirectX::XMConvertToRadians(frame / 2)) * 100;

	//‚Ó‚Ÿ‚ñ‚Ó‚Ÿ‚ñ‚Ì‚½‚Ü‚½‚Ü
	if (!m_funnelPause)
	{
		if (m_funnelBulSpeed == 120)
		{
			m_funnelBulFast = 20.0f;
		}
		else if (m_funnelBulSpeed < 120 && m_funnelBulSpeed >= 100)
		{
			m_funnelBulFast = 25.0f;
		}
		else if(m_funnelBulSpeed < 100 && m_funnelBulSpeed >= 80)
		{
			m_funnelBulFast = 30.0f;
		}
		else if (m_funnelBulSpeed < 80 && m_funnelBulSpeed >= 60)
		{
			m_funnelBulFast = 35.0f;
		}
		else if (m_funnelBulSpeed < 60 && m_funnelBulSpeed >= 40)
		{
			m_funnelBulFast = 40.0f;
		}
		else if (m_funnelBulSpeed < 40 && m_funnelBulSpeed >= 20)
		{
			m_funnelBulFast = 45.0f;
		}

		
		for (auto& enemy : m_pOwner->GetEnemyAList())
		{
			if (enemy->GetFlg())
			{
				m_target = enemy->GetPos() - m_pos;

				m_smallest = m_target.Length();

				if (m_smallest <= m_smallestNext)
				{
					m_smallestNext = m_smallest;
					m_smallestPos = enemy->GetPos();
				}

				if (bulframe >= m_funnelBulSpeed)
				{
					std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

					tempBullet->Init();

					tempBullet->SetTexture(&m_bulletTex);

					tempBullet->Shot({ m_pos }, Funnel, { m_smallestPos },m_funnelBulFast);

					m_pOwner->AddBullet(tempBullet);

					m_angle = atan2(m_smallestPos.y - m_pos.y, m_smallestPos.x - m_pos.x);

					bulframe = 0;
				}
			}
		}

		animeframe++;

		if (animeframe > 10)
		{
			m_funnelAnimeCnt++;
			animeframe = 0;
			if (m_funnelAnimeCnt > 3)
			{
				m_funnelAnimeCnt = 0;
			}
		}
	}
	

	m_smat = Math::Matrix::CreateScale(1, 1, 0);
	m_rmat = Math::Matrix::CreateRotationZ(m_angle);
	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_smat * m_rmat * m_tmat;
}

void C_Funnel::Draw()
{
	if (!m_funnelPause)
	{
		switch (m_funnelAnimeCnt)
		{
		case 0:
			DrawImg(m_mat, &m_Tex, { 0,0,32,32 }, 1.0f);
			break;
		case 1:
			DrawImg(m_mat, &m_Tex, { 32,0,32,32 }, 1.0f);
			break;
		case 2:
			DrawImg(m_mat, &m_Tex, { 64,0,32,32 }, 1.0f);
			break;
		case 3:
			DrawImg(m_mat, &m_Tex, { 96,0,32,32 }, 1.0f);
			break;
		}
	}
}
