#include "../Scene/Scene.h"
#include "../Attack/Bullet.h"
#include "Player.h"

void C_Player::Init()
{
	m_playerTex.Load("Texture/Player/player.png");
	m_C_kasanTex.Load("Texture/Kasan/kasan_color.png");
	m_BulletTex.Load("Texture/Bullet/player_bulY.png");
	m_pos = { -500,0 };
	//m_pos = { 0,0 };
	frame = 0;
	frame2 = 0;
	frame3 = 0;
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
	m_UpAnimeCnt = 0;
	m_UpAnimeCnt = 0;

	m_funnel.Init();
}

void C_Player::Update()
{
	frame++;
	frame2++;

	m_funnel.Update();

	if (!m_playerPauseFlg)
	{

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

		//‚±‚Á‚©‚çƒAƒrƒŠƒeƒB‚â‚è‚Ü‚·


		for (int a = 0; a < abilityMax; a++)
		{
			if (m_ability[a] > 0)continue;

			if (!m_UseFlg)
			{
				m_ability[a] = m_abi;
				m_zero = true;
				m_UseFlg = true;
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
		}



		m_pOwner->SetDebug1(m_ability[0]);
		m_pOwner->SetDebug2(m_ability[1]);
		m_pOwner->SetDebug3(m_ability[2]);

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

			//’e‚Ì”­Ëˆ—
			if (frame >= m_bulSpeed)
			{
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
				{
					if (m_plusbullet == 5)
					{
						//‚P‰ñ–Ú
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 50 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚Q‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 30 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚R‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10}, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚S‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚T‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 30 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚T‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 50 }, 0);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 4)
					{
						//‚P‰ñ–Ú
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 40 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚Q‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 20 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚R‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y  }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚S‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 20 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚T‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 40 }, 0);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 3)
					{
						//‚P‰ñ–Ú
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 30 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚Q‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚R‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚S‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 30 }, 0);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 2)
					{
						//‚P‰ñ–Ú
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 20 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚Q‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y  }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚R‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 20 }, 0);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else if (m_plusbullet == 1)
					{
						//‚P‰ñ–Ú
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y + 10 }, 0);

						m_pOwner->AddBullet(tempBullet);

						//‚Q‰ñ–Ú
						tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10,m_pos.y - 10 }, 0);

						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
					else
					{
						std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

						tempBullet->Init();

						tempBullet->SetTexture(&m_BulletTex);

						tempBullet->Shot({ m_pos.x + 10 , m_pos.y}, 0);

						//m_bulletList.push_back(tempBullet);	// push_back : ”z—ñ‚Ì––”ö‚Éƒf[ƒ^‚ğ’Ç‰Á‚·‚é
						m_pOwner->AddBullet(tempBullet);

						frame = 0;
					}
				}
			}
		}

	}

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

	//‰æ–ÊŠO‚Éo‚ê‚È‚¢
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

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Player::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	m_funnel.Draw();

	D3D.SetBlendState(BlendMode::Add);
	DrawImg(m_mat, &m_C_kasanTex, { 128,0,64,64 }, 1.0f);	//F•t‚«‚Ì‰ÁZ‡¬
	D3D.SetBlendState(BlendMode::Alpha);

	
	if (m_playerUpFlg&&!m_playerDownFlg)
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

	if (m_playerDownFlg&&!m_playerUpFlg)
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

	/*for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw(0);
	}*/

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
