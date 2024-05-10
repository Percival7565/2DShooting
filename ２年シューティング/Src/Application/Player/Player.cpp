#include "../Scene/Scene.h"
#include "../Attack/Bullet.h"
#include "Player.h"

void C_Player::Init()
{
	m_playerTex.Load("Texture/Player/player.png");
	m_C_kasanTex.Load("Texture/Kasan/kasan_color.png");
	m_BulletTex.Load("Texture/Bullet/bullet.png");
	m_HpTex.Load("Texture/UI/player_hp.png");
	m_HpkasanTex.Load("Texture/UI/hp_kasan3.png");
	m_pos = { -500,0 };
	//m_pos = { 0,0 };
	frame = 0;
	frame2 = 0;
	frame3 = 0;
	frame4 = 0;
	m_bFlg = true;

	m_playerAnimeCnt = 0;

	for (int a = 0; a < abilityMax; a++)
	{
		m_ability[a] = 0;
		m_abilityUseFlg[a] = false;
	}
	m_plusbullet = 0;
	m_plusbulSize = 0;
	m_plusbulSpeed = 0;
	m_bulSpeed = 60;
	
	m_abi = 0;
	m_zero = false;
	m_UseFlg = false;
	m_playerPauseFlg = false;
	m_playerUpFlg = false;
	m_playerDownFlg = false;
	m_InFlg = false;
	m_UpAnimeCnt = 0;
	m_UpAnimeCnt = 0;

	m_playerColor = 0;
	m_playerHp = 5;
	m_HpAlpha = 1.0f;

	m_plusFunnel = 140;
	m_funnelFlg = false;
	m_funnel.Init();
	m_funnel.SetOwner(m_pOwner);
	
}

void C_Player::Update()
{
	frame++;
	frame2++;
	frame4++;

	if (m_playerHp <= 0)
	{
		m_bFlg = false;
	}

	if (!m_playerPauseFlg)
	{
		//m_funnel.SetPause(false);

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x = m_pos.x + 10;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x = m_pos.x - 10;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_pos.y = m_pos.y + 10;
			m_playerUpFlg = true;
		}
		else
		{
			m_playerUpFlg = false;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_pos.y = m_pos.y - 10;
			m_playerDownFlg = true;
		}
		else
		{
			m_playerDownFlg = false;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_playerColor = 0;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_playerColor = 1;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_playerColor = 2;
		}

		if (GetAsyncKeyState('F') & 0x8000)
		{
			m_playerColor = 3;
		}

		//Ç±Ç¡Ç©ÇÁÉAÉrÉäÉeÉBÇ‚ÇËÇ‹Ç∑


		for (int a = 0; a < abilityMax; a++)
		{
			if (m_ability[a] > 0)continue;

			if (!m_UseFlg)
			{
				m_ability[a] = m_abi;
				m_zero = true;
				m_UseFlg = true;
				//m_InFlg = true;
			}

			if (m_abi == 0)m_UseFlg = false;

			//m_ability[a] = m_abi;

			/*if (m_abilityUseFlg[a] == false)
			{
				m_ability[a] = m_abi;

				if (m_ability[a] > 0)
				{
					m_abilityUseFlg[a] = true;
				}
			}*/

			if (m_ability[a] == 1)
			{
				m_plusbullet++;
			}

			if (m_ability[a] == 2)
			{
				m_plusbulSize++;
			}

			if (m_ability[a] == 3)
			{
				m_plusbulSpeed++;
			}

			if (m_ability[a] == 4)
			{
				m_funnelFlg = true;
				m_funnel.SetPause(false);
				m_plusFunnel -= 20;
				m_funnel.SetBulSpeed(m_plusFunnel);
			}
			else
			{
				//m_funnel.SetPause(true);
			}
		}

		m_pOwner->pa = m_ability[0];
		m_pOwner->pb = m_ability[1];
		m_pOwner->pc = m_ability[2];
		m_pOwner->pd = m_ability[3];
		m_pOwner->pe = m_ability[4];

		//m_pOwner->SetDebug1(m_plusFunnel);

		//m_pOwner->SetDebug1(m_ability[0]);
		//m_pOwner->SetDebug2(m_ability[1]);
		//m_pOwner->SetDebug3(m_ability[2]);

		// m_pBullet.SetPlayerBulSizeLv(m_plusbulSize);

		switch (m_plusbulSpeed)
		{
		case 0:
			m_bulSpeed = 60;
			break;
		case 1:
			m_bulSpeed = 50;
			break;
		case 2:
			m_bulSpeed = 40;
			break;
		case 3:
			m_bulSpeed = 30;
			break;
		case 4:
			m_bulSpeed = 20;
			break;
		case 5:
			m_bulSpeed = 5;
			break;
		default:
			m_bulSpeed = 60;
			break;
		}


		if (m_bFlg)
		{

			//íeÇÃî≠éÀèàóù
			if (frame >= m_bulSpeed)
			{
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
				{

					

					if (m_plusbullet == 5)
					{
						//ÇPâÒñ⁄
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 50 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇQâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 30 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇRâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10}, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇSâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇTâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 30 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇUâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 50 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 4)
					{
						//ÇPâÒñ⁄
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 40 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇQâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 20 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇRâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y  }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇSâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 20 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇTâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 40 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 3)
					{
						//ÇPâÒñ⁄
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 30 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇQâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇRâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇSâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 30 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 2)
					{
						//ÇPâÒñ⁄
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 20 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇQâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y  }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇRâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 20 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 1)
					{
						//ÇPâÒñ⁄
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						//ÇQâÒñ⁄
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, m_playerColor);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else
					{
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						m_pOwner->m_sound.SE_Inst[se_Shot]->Play();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10 , m_pos.y}, m_playerColor);

						//m_bulletList.push_back(tempBullet);	// push_back : îzóÒÇÃññîˆÇ…ÉfÅ[É^Çí«â¡Ç∑ÇÈ
						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
				}
			}

			m_funnel.Update(m_pos);
		}

	}
	else
	{
		if (!m_funnelFlg)
		{
			m_funnel.SetPause(true);
		}
		else
		{
			m_funnel.SetPause(false);
		}
	}

	//m_funnel.Update(m_pos);

	if (frame2 > 20)
	{
		m_playerAnimeCnt++;
		frame2 = 0;
		if (m_playerAnimeCnt >= 4)
		{
			m_playerAnimeCnt = 0;
		}
	}

	if (!m_playerDownFlg && !m_playerUpFlg)
	{
		frame3 = 0;
	}

	if (m_playerUpFlg)
	{
		frame3++;
		if (frame3 > 10)
		{
			m_UpAnimeCnt = 1;
			frame3 = 0;
		}
	}
	else
	{
		m_UpAnimeCnt = 0;
	}

	if (m_playerDownFlg)
	{
		frame3++;
		if (frame3 > 10)
		{
			m_DownAnimeCnt = 1;
			frame3 = 0;
		}
	}
	else
	{
		m_DownAnimeCnt = 0;
	}

	//âÊñ äOÇ…èoÇÍÇ»Ç¢
	if (m_pos.x <= -640 + 32)
	{
		m_pos.x = -640 + 32;
	}

	if (m_pos.x >= 640 + -32)
	{
		m_pos.x = 640 + -32;
	}

	if (m_pos.y <= -360 + 32)
	{
		m_pos.y = -360 + 32;
	}

	if (m_pos.y >= 360 + -32)
	{
		m_pos.y = 360 + -32;
	}

	
	if (m_pos.x < -300 && m_pos.y > 260)
	{
		m_HpAlpha = 0.5f;
	}
	else
	{
		m_HpAlpha = 1.0f;
	}
	

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_HpSMat = Math::Matrix::CreateScale(3, 3, 0); 
	m_HpTMat = Math::Matrix::CreateTranslation(-480, 300, 0);
	m_HpMat = m_HpSMat * m_HpTMat;

	m_HpkasanSMat = CreateScale(3.2f,3.5f,0);
	m_HpkasanMat = m_HpkasanSMat * m_HpTMat;
}

void C_Player::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	m_funnel.Draw();

	D3D.SetBlendState(BlendMode::Add);

	switch (m_playerColor)
	{
	case 0 :
		DrawImg(m_mat, &m_C_kasanTex, { 0,0,64,64 }, 1.0f);	//êFïtÇ´ÇÃâ¡éZçáê¨
		break;
	case 1:
		DrawImg(m_mat, &m_C_kasanTex, { 64,0,64,64 }, 1.0f);	//êFïtÇ´ÇÃâ¡éZçáê¨
		break;
	case 2:
		DrawImg(m_mat, &m_C_kasanTex, { 128,0,64,64 }, 1.0f);	//êFïtÇ´ÇÃâ¡éZçáê¨
		break;
	case 3:
		DrawImg(m_mat, &m_C_kasanTex, { 192,0,64,64 }, 1.0f);	//êFïtÇ´ÇÃâ¡éZçáê¨
		break;
	}
	D3D.SetBlendState(BlendMode::Alpha);

	switch (m_playerColor)
	{
	case 0:

		if (m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_UpAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 256,0,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 320,0,64,64 }, 1.0f);
				break;
			}
		}

		if (m_playerDownFlg && !m_playerUpFlg)
		{
			switch (m_DownAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 384,0,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 448,0,64,64 }, 1.0f);
				break;
			}
		}

		if (!m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_playerAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 0,0,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 64,0,64,64 }, 1.0f);
				break;
			case 2:
				DrawImg(m_mat, &m_playerTex, { 128,0,64,64 }, 1.0f);
				break;
			case 3:
				DrawImg(m_mat, &m_playerTex, { 192,0,64,64 }, 1.0f);
				break;
			}
		}
		else
		{
			if (m_playerUpFlg && m_playerDownFlg)
			{
				switch (m_playerAnimeCnt)
				{
				case 0:
					DrawImg(m_mat, &m_playerTex, { 0,0,64,64 }, 1.0f);
					break;
				case 1:
					DrawImg(m_mat, &m_playerTex, { 64,0,64,64 }, 1.0f);
					break;
				case 2:
					DrawImg(m_mat, &m_playerTex, { 128,0,64,64 }, 1.0f);
					break;
				case 3:
					DrawImg(m_mat, &m_playerTex, { 192,0,64,64 }, 1.0f);
					break;
				}
			}
		}
		break;
	case 1:
		if (m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_UpAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 256,64,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 320,64,64,64 }, 1.0f);
				break;
			}
		}

		if (m_playerDownFlg && !m_playerUpFlg)
		{
			switch (m_DownAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 384,64,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 448,64,64,64 }, 1.0f);
				break;
			}
		}

		if (!m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_playerAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 0,64,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 64,64,64,64 }, 1.0f);
				break;
			case 2:
				DrawImg(m_mat, &m_playerTex, { 128,64,64,64 }, 1.0f);
				break;
			case 3:
				DrawImg(m_mat, &m_playerTex, { 192,64,64,64 }, 1.0f);
				break;
			}
		}
		else
		{
			if (m_playerUpFlg && m_playerDownFlg)
			{
				switch (m_playerAnimeCnt)
				{
				case 0:
					DrawImg(m_mat, &m_playerTex, { 0,64,64,64 }, 1.0f);
					break;
				case 1:
					DrawImg(m_mat, &m_playerTex, { 64,64,64,64 }, 1.0f);
					break;
				case 2:
					DrawImg(m_mat, &m_playerTex, { 128,64,64,64 }, 1.0f);
					break;
				case 3:
					DrawImg(m_mat, &m_playerTex, { 192,64,64,64 }, 1.0f);
					break;
				}
			}
		}
		break;
	case 2:
		if (m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_UpAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 256,128,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 320,128,64,64 }, 1.0f);
				break;
			}
		}

		if (m_playerDownFlg && !m_playerUpFlg)
		{
			switch (m_DownAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 384,128,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 448,128,64,64 }, 1.0f);
				break;
			}
		}

		if (!m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_playerAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 0,128,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 64,128,64,64 }, 1.0f);
				break;
			case 2:
				DrawImg(m_mat, &m_playerTex, { 128,128,64,64 }, 1.0f);
				break;
			case 3:
				DrawImg(m_mat, &m_playerTex, { 192,128,64,64 }, 1.0f);
				break;
			}
		}
		else
		{
			if (m_playerUpFlg && m_playerDownFlg)
			{
				switch (m_playerAnimeCnt)
				{
				case 0:
					DrawImg(m_mat, &m_playerTex, { 0,128,64,64 }, 1.0f);
					break;
				case 1:
					DrawImg(m_mat, &m_playerTex, { 64,128,64,64 }, 1.0f);
					break;
				case 2:
					DrawImg(m_mat, &m_playerTex, { 128,128,64,64 }, 1.0f);
					break;
				case 3:
					DrawImg(m_mat, &m_playerTex, { 192,128,64,64 }, 1.0f);
					break;
				}
			}
		}
		break;
	case 3:
		if (m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_UpAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 256,192,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 320,192,64,64 }, 1.0f);
				break;
			}
		}

		if (m_playerDownFlg && !m_playerUpFlg)
		{
			switch (m_DownAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 384,192,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 448,192,64,64 }, 1.0f);
				break;
			}
		}

		if (!m_playerUpFlg && !m_playerDownFlg)
		{
			switch (m_playerAnimeCnt)
			{
			case 0:
				DrawImg(m_mat, &m_playerTex, { 0,192,64,64 }, 1.0f);
				break;
			case 1:
				DrawImg(m_mat, &m_playerTex, { 64,192,64,64 }, 1.0f);
				break;
			case 2:
				DrawImg(m_mat, &m_playerTex, { 128,192,64,64 }, 1.0f);
				break;
			case 3:
				DrawImg(m_mat, &m_playerTex, { 192,192,64,64 }, 1.0f);
				break;
			}
		}
		else
		{
			if (m_playerUpFlg && m_playerDownFlg)
			{
				switch (m_playerAnimeCnt)
				{
				case 0:
					DrawImg(m_mat, &m_playerTex, { 0,192,64,64 }, 1.0f);
					break;
				case 1:
					DrawImg(m_mat, &m_playerTex, { 64,192,64,64 }, 1.0f);
					break;
				case 2:
					DrawImg(m_mat, &m_playerTex, { 128,192,64,64 }, 1.0f);
					break;
				case 3:
					DrawImg(m_mat, &m_playerTex, { 192,192,64,64 }, 1.0f);
					break;
				}
			}
		}
		break;
	}

	D3D.SetBlendState(BlendMode::Add);

	//DrawImg(m_HpkasanMat, &m_HpkasanTex, { 0,0,80,16 }, m_HpAlpha - sin(DirectX::XMConvertToRadians(frame4)) * 0.1f);
	DrawImg(m_HpkasanMat, &m_HpkasanTex, { 0,0,80,16 }, m_HpAlpha - sin(DirectX::XMConvertToRadians(frame4 * 2) * 0.2f));

	switch (m_playerHp)
	{
	case 0:
		DrawImg(m_HpMat, &m_HpTex, { 0,0,80,16 }, m_HpAlpha);
		break;
	case 1:
		DrawImg(m_HpMat, &m_HpTex, { 0,64,80,16 }, m_HpAlpha);
		break;
	case 2:
		DrawImg(m_HpMat, &m_HpTex, { 0,48,80,16 }, m_HpAlpha);
		break;
	case 3:
		DrawImg(m_HpMat, &m_HpTex, { 0,32,80,16 }, m_HpAlpha);
		break;
	case 4:
		DrawImg(m_HpMat, &m_HpTex, { 0,16,80,16 }, m_HpAlpha);
		break;
	case 5:
		DrawImg(m_HpMat, &m_HpTex, { 0,0,80,16 }, m_HpAlpha);
		break;
	default:
		break;
	}
	D3D.SetBlendState(BlendMode::Alpha);
}

HitStruct C_Player::GetObj()
{
	HitStruct m_Obj;
	m_Obj.pos = m_pos;
	m_Obj.rad = {50,50};
	m_Obj.move = {0,0};
	m_Obj.bActive = m_bFlg;

	return HitStruct(m_Obj);
}
