#include "main.h"
#include "Scene.h"


void Scene::Draw2D()
{
	switch (nowScene)
	{
	case SceneType::Title:
		DrawTitle();
		break;
	case SceneType::Game:
		DrawGame();
		break;
	case SceneType::Result:
		DrawResult();
		break;
	default:
		break;
	}

	// ▼▼▼文字列はほかの描画が終わってから書くこと！▲▲▲
	// 文字列表示
	//SHADER.m_spriteShader.DrawString(640 - 340, 360 - 10, "ベースプログラム", Math::Vector4(0, 0, 0, frame / (60.0f * 10) ));
	//SHADER.m_spriteShader.DrawString(640 - 344, 360 - 14, "ベースプログラム", Math::Vector4(1, 1, 0, frame / (60.0f * 10) ));

}

void Scene::DrawTitle()
{
	m_back.Draw();
	DrawImg(m_BlackMat, &m_ChangeBlackTex, { 0,0,1280,720 }, m_BlackAlpha);
	m_title.Draw();

	D3D.SetBlendState(BlendMode::Add);
	DrawImg(m_PushMat, &m_PushEnterTex, { 0,0,500,50 }, m_pushAlpha);
	D3D.SetBlendState(BlendMode::Alpha);
	//SHADER.m_spriteShader.DrawString(titleX, titleY, "タイトル画面", Math::Vector4(1, 1, 0, 1));
}

void Scene::UpdateTitle()
{
	frame2++;
	m_title.Update();

	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
			m_SceneChange = true;
			
		}
	}
	else
	{
		keyFlg = false;
	}
	
	if (m_SceneChange)
	{
		m_TitleCnt++;
		m_BlackAlpha += 0.008;
		m_pushAlpha -= 0.05f;

		if (m_BlackAlpha >= 1.0f)
		{
			m_BlackAlpha = 1.0f;
		}
		
		m_title.SetTakeFlg(false);

		if (m_TitleCnt >= 100)
		{
			m_TitleOutAlphaA -= 0.005;
			m_TitleOutAlphaB -= 0.005;

			if (m_TitleOutAlphaA <= 0.0f)
			{
				m_TitleOutAlphaA = 0.0f;
			}
			if (m_TitleOutAlphaB <= 0.0f)
			{
				m_TitleOutAlphaB = 0.0f;
			}

			m_title.SetAalpha(m_TitleOutAlphaA);
			m_title.SetBalpha(m_TitleOutAlphaB);
		}
		else
		{
			m_TitleOutAlphaA = m_title.GetAalpha();
			m_TitleOutAlphaB = m_title.GetBalpha();
		}

		if (m_TitleCnt >= 180)
		{
			InitGame();
			nowScene = SceneType::Game;
		}
	}
	else
	{
		m_pushAlpha = (sin(DirectX::XMConvertToRadians(frame2)) * 0.5f) + 0.6f;
	}

	m_BlackMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_PushMat = Math::Matrix::CreateTranslation(0, -200, 0);
}

void Scene::InitTitle()
{
	frame2 = 0;
	m_pushAlpha = 0;
	m_title.Init();
	m_TitleCnt = 0;
	m_SceneChange = false;
	m_BlackAlpha = 0.0f;
	m_TitleOutAlphaA = 0.0f;
	m_TitleOutAlphaB = 0.0f;
}

void Scene::DrawGame()
{
	m_back.Draw();

	
	for (auto& enemyA : m_enemyAList)
	{
		enemyA->Draw();
	}

	for (auto& enemyB : m_enemyBList)
	{
		enemyB->Draw();
	}

	for (auto& enemyC : m_enemyCList)
	{
		enemyC->Draw();
	}

	for (auto& enemyD : m_enemyDList)
	{
		enemyD->Draw();
	}

	m_player.Draw();

	m_status.Draw();

	if (m_GameFlow == 1)
	{
		for (auto& bullet : m_bulletList)
		{
			bullet->Draw();
		}
	}

	m_wave.Draw();
	//デバッグ
	//m_number.DrawLeft(123456,{0,0});

	DrawImg(m_BlackMat, &m_ChangeBlackTex, { 0,0,1280,720 }, m_BlackAlpha);

	if (m_GameFlow == 2)
	{
		if (m_NowWave <= 5)
		{
			m_ability.Draw();
		}
	}

	//m_number.DrawLeft(0, { 0,0 });
	//SHADER.m_spriteShader.DrawString(100, -200, "%d", Math::Vector4(1, 1, 1, 1));

	char text[200];
	sprintf_s(text, sizeof(text), "%02d : %02d", m_TimeMinutes,m_Time);
	SHADER.m_spriteShader.DrawString(400, 320, text, Math::Vector4(1, 1, 1, 1));

	//m_ability.Draw();
}

void Scene::UpdateGame()
{

	m_player.SetAbility(m_ability.GetSelectAbi());
	m_player.Update();
	if (m_player.GetZero())
	{
		m_ability.SetGetAbi(0);
	}
	
	switch (m_GameFlow)
	{
	case 0:
		m_GameFrame++;

		if (m_BlackAlpha < 0.0f)
		{
			m_BlackAlpha = 0.0f;
		}
		else
		{

			m_BlackAlpha -= 0.008;
		}

		/*if (m_GameFrame < 10)
		{
			m_wave.SetWaveScale({0,0});
		}*/

		if (m_GameFrame >= 80)
		{
			m_wave.SetWaveFlg(true);
			m_wave.Update();
		}
		else
		{
			//m_player.SetPos({ -500,0 });
			//Pause(true);
		}

		if (m_GameFrame >= 240)
		{
			m_GameFlow = 1;
			m_wave.SetWaveFlg(false);
			m_player.SetPause(false);
		}
		else
		{
			m_player.SetPause(true);
		}
		break;
	case 1:

		m_back.Update();

		m_Timeframe++;

		m_Time = m_Timeframe / 60;

		//m_TimeMinutes = m_Timeframe / 60 / 60;

		if (m_Time >= 60)
		{
			m_Timeframe = 0;
			m_Time = 0;
			m_TimeMinutes += 1;
		}

		if (m_EnemyFrame == 0)
		{
			switch (m_NowWave)
			{
			case 0:
				break;
			case 1:
				MakeEnemyA({ 200,300 }, 0);
				MakeEnemyA({ 200,-300 }, 0);
				break;
			case 2:
				MakeEnemyA({ 200,-300 }, 1);
				MakeEnemyA({ 100,-300 }, 1);
				MakeEnemyA({ 100,300 }, 1);
				MakeEnemyA({ 200,300 }, 1);
				break;
			case 3:
				MakeEnemyA({ 100,-300 }, 1);
				MakeEnemyA({ 100,300 }, 1);
				MakeEnemyB({ 200,0 }, 2);
				break;
			case 4:
				MakeEnemyC({ 300,-200 }, 1);
				MakeEnemyC({ 300,200 }, 1);
				MakeEnemyB({ 400,-50 }, 2);
				MakeEnemyB({ 200,50 }, 2);
				break;
			case 5:
				MakeEnemyA({ -100,-300 }, 1); 
				MakeEnemyA({ -100, 300 }, 1);
				MakeEnemyC({ 300,-200 }, 1);
				MakeEnemyC({ 300, 200 }, 1);
				MakeEnemyC({ 300, 250 }, 1);
				MakeEnemyC({ 300,-250 }, 1);
				break;
			case 6:
				MakeEnemyD({ 730,100 }, 3);
				MakeEnemyD({ 730,-100 }, 3);
				MakeEnemyA({ 100,-300 }, 0);
				MakeEnemyA({ 100,-300 }, 0);
				MakeEnemyB({ 400,-100 }, 2);
				MakeEnemyB({ 200,100 }, 2);
				break;
			case 7:
				MakeEnemyD({ 730,-100 }, 3);
				MakeEnemyD({ 730, 100 }, 3);
				MakeEnemyA({ 100,-300 }, 0);
				MakeEnemyA({ 100, 300 }, 0);
				MakeEnemyA({ 50,-300 }, 0);
				MakeEnemyA({ 50, 300 }, 0);
				MakeEnemyA({ 200,-100 }, 0);
				MakeEnemyA({ 200, 100 }, 0);
				break;
			case 8:
				MakeEnemyD({ 730,-200 }, 3);
				MakeEnemyD({ 730, 200 }, 3);
				MakeEnemyB({ 600,-200 }, 2);
				MakeEnemyB({ 600,200 }, 2);
				MakeEnemyA({ 400,-300 }, 0);
				MakeEnemyA({ 400, 300 }, 0);
				MakeEnemyC({ 750,-200 }, 1);
				MakeEnemyC({ 750, 200 }, 1);
				break;
			case 9:
				
				break;
			}
		}

		//プレイヤーももともとここにいた
		
		

		for (auto& enemyA : m_enemyAList)
		{
			enemyA->Update();
		}

		for (auto& enemyB : m_enemyBList)
		{
			enemyB->Update();
		}

		for (auto& enemyC : m_enemyCList)
		{
			enemyC->Update();
		}

		for (auto& enemyD : m_enemyDList)
		{
			enemyD->Update();
		}

		m_status.Update();

		PlayerBul_EnemyA();//プレイヤーの弾と敵本体の当たり判定
		FunnelBul_Enemy();//ファンネルと敵本体の当たり判定
		EnemyBul_Player();//敵の弾とプレイヤー本体の当たり判定

		m_hit.GetHitJet();


		for (int b = 0; b < m_bulletList.size(); b++)
		{
			m_bulletList[b]->SetColor(m_player.GetPlayerColor());
			m_bulletList[b]->SetPlayerBulSizeLv(m_player.GetBulletSize());
			m_bulletList[b]->Update();
		}


		if (m_EnemyFrame >= 100)
		{
			if (m_WaveEnemyNum == 0)
			{
				for (int b = 0; b < m_bulletList.size(); b++)
				{
					m_bulletList[b]->SetAlive(false);
				}
				m_WavePlusFlg = false;
				m_GameFlow = 2;
			}
		}
		else
		{
			m_EnemyFrame++;
		}

		if (GetAsyncKeyState('E') & 0x8000)
		{
			m_player.SetFlg(false);
		}
		else
		{
			m_player.SetFlg(true);
		}
		

		if (!m_player.GetFlg())
		{
			for (auto& enemyA : m_enemyAList)
			{
				enemyA->SetFlg(false);
			}
			for (auto& enemyB : m_enemyBList)
			{
				enemyB->SetFlg(false);
			}
			for (auto& enemyC : m_enemyCList)
			{
				enemyC->SetFlg(false);
			}
			for (auto& enemyD : m_enemyDList)
			{
				enemyD->SetFlg(false);
			}
			InitResult();
			nowScene = SceneType::Result;
		}
		

		break;
	case 2:
		//m_player.SetPause(true);

		if (m_NowWave == 9)
		{
			for (auto& enemyA : m_enemyAList)
			{
				enemyA->SetFlg(false);
			}
			for (auto& enemyB : m_enemyBList)
			{
				enemyB->SetFlg(false);
			}
			for (auto& enemyC : m_enemyCList)
			{
				enemyC->SetFlg(false);
			}
			for (auto& enemyD : m_enemyDList)
			{
				enemyD->SetFlg(false);
			}
			InitResult();
			nowScene = SceneType::Result;
		}

		
		
		if (!m_WavePlusFlg)
		{
			m_ability.SetFrame(0);
			m_BlackAlpha = 0.5f;
			m_GameFrame = 0;
			m_EnemyFrame = 0;
			m_NowWave += 1;
			m_wave.Init();
			m_wave.SetWaveNum(m_NowWave);

			if (m_player.GetHp() < 5)
			{
				m_player.SetHp(m_player.GetHp() + 1);
			}
			
			m_WavePlusFlg = true;
			
		}

		if (m_NowWave <= 5)
		{
			m_ability.Update();
		}
		else
		{
			m_ability.Init();
			m_GameFlow = 0;
		}
		
		if (GetAsyncKeyState('V') & 0x8000)
		{
			//m_ability.ReRoll();
			m_ability.Init();
			m_GameFlow = 0;
		}
		break;
	default:
		break;
	}

	
	

	std::vector<std::shared_ptr<C_Bullet>>::iterator it;

	it = m_bulletList.begin();

	while (it != m_bulletList.end())
	{
		const bool bAlive = (*it)->GetAlive();
		if (!bAlive)
		{
			it = m_bulletList.erase(it);
		}
		else
		{
			it++;
		}
	}

	//デバッグ
	if (GetAsyncKeyState('P') & 0x8000)
	{
		Pause(true);
	}
	else
	{
		Pause(false);
	}
	

	/*if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
			InitResult();
			nowScene = SceneType::Result;
		}
	}
	else
	{
		keyFlg = false;
	}*/

	m_BlackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void Scene::InitGame()
{
	m_NowWave = 1; 
	m_WavePlusFlg = false;

	m_Time = 0;
	m_Timeframe = 0;
	m_TimeMinutes = 0;

	

	m_GameFlow = 0;
	m_GameFrame = 0;

	m_WaveEnemyNum = 0;
	m_EnemyFrame = 0;

	m_wave.Init();

	m_player.Init();

	m_status.Init();

	m_ability.Init();

	//m_BlackAlpha = 1.0f;

	//m_enemyA[0]->Init();

	//for (int i = 0; i < 10; i++)
	//{
	//	//C_EnemyA* enemyA = new C_EnemyA();
	//	std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
	//	tempEnemy->SetOwner(this);
	//	tempEnemy->Init();
	//	tempEnemy->SetPos({ 640.0f + (i * 100.0f),0.0f});
	//	//tempEnemy->SetPos({0,0});
	//	m_enemyAList.push_back(tempEnemy);
	//}
}

void Scene::DrawResult()
{
	m_back.Draw();

	if (m_player.GetFlg())
	{
		//SHADER.m_spriteShader.DrawString(0,0, "リザルト画面", Math::Vector4(1, 1, 0, 1));
		switch (m_rank)
		{
		case 0:
			DrawImg(m_RankMat, &m_RankTex, { 0,0,50,50 }, m_rankAlpha);
			break;
		case 1:
			DrawImg(m_RankMat, &m_RankTex, { 50,0,50,50 }, m_rankAlpha);
			break;
		case 2:
			DrawImg(m_RankMat, &m_RankTex, { 100,0,50,50 }, m_rankAlpha);
			break;
		case 3:
			DrawImg(m_RankMat, &m_RankTex, { 150,0,50,50 }, m_rankAlpha);
			break;
		default:
			break;
		}

		char text[200];
		sprintf_s(text, sizeof(text), "クリアタイム%02d : %02d", m_TimeMinutes, m_Time);
		SHADER.m_spriteShader.DrawString(0, 0, text, Math::Vector4(1, 1, 1, 1));
		SHADER.m_spriteShader.DrawString(-200, 50, "Rank", Math::Vector4(1, 1, 1, 1));
	}
	else
	{
		DrawImg(m_GameOverMat, &m_GameOverTex, { 0,0,500,50 }, 1.0f);
	}
	SHADER.m_spriteShader.DrawString(400, -300, "ENTERキーでタイトル", Math::Vector4(1, 1, 0, (sin(DirectX::XMConvertToRadians(resultframe)) * 0.5f) + 0.6f));
}

void Scene::UpdateResult()
{
	frame3++;
	resultframe++;

	if (m_TimeMinutes <= 1)
	{
		m_rank = 0;
	}
	else if (m_TimeMinutes > 1 && m_TimeMinutes <= 2)
	{
		m_rank = 1;
	}
	else if (m_TimeMinutes > 2 && m_TimeMinutes <= 3)
	{
		m_rank = 2;
	}
	else if (m_TimeMinutes > 3 && m_TimeMinutes <= 3)
	{
		m_rank = 3;
	}

	m_rankAlpha = (sin(DirectX::XMConvertToRadians(frame3)) * 0.5f) + 0.6f;

	m_RankTMat = Math::Matrix::CreateTranslation(-100,0,0);
	m_RankSMat = Math::Matrix::CreateScale(3);
	m_RankMat = m_RankSMat * m_RankTMat;

	m_GameOverMat = Math::Matrix::CreateTranslation(0, 0, 0);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
			InitTitle();
			InitGame();
			nowScene = SceneType::Title;
		}
	}
	else
	{
		keyFlg = false;
	}
}

void Scene::InitResult()
{
	resultframe = 0;
	frame3 = 0;
	m_rankAlpha = 0.0f;
}

void Scene::MakeEnemyA(Math::Vector2 a_pos, int a_type)
{
	std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
	m_WaveEnemyNum++;
	m_EnemyFrame = 0;
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	tempEnemy->SetMoveType(a_type);
	tempEnemy->SetPos(a_pos);
	m_enemyAList.push_back(tempEnemy);
}

void Scene::MakeEnemyB(Math::Vector2 a_pos, int a_type)
{
	std::shared_ptr<C_EnemyB> tempEnemy = std::make_shared<C_EnemyB>();
	m_WaveEnemyNum++;
	m_EnemyFrame = 0;
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	tempEnemy->SetMoveType(a_type);
	tempEnemy->SetPos(a_pos);
	m_enemyBList.push_back(tempEnemy);
}

void Scene::MakeEnemyC(Math::Vector2 a_pos, int a_type)
{
	std::shared_ptr<C_EnemyC> tempEnemy = std::make_shared<C_EnemyC>();
	m_WaveEnemyNum++;
	m_EnemyFrame = 0;
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	tempEnemy->SetMoveType(a_type);
	tempEnemy->SetPos(a_pos);
	m_enemyCList.push_back(tempEnemy);
}

void Scene::MakeEnemyD(Math::Vector2 a_pos, int a_type)
{
	std::shared_ptr<C_EnemyD> tempEnemy = std::make_shared<C_EnemyD>();
	m_WaveEnemyNum++;
	m_EnemyFrame = 0;
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	tempEnemy->SetMoveType(a_type);
	tempEnemy->SetPos(a_pos);
	m_enemyDList.push_back(tempEnemy);
}

void Scene::PlayerBul_EnemyA()
{
	for (auto& bul : m_bulletList)
	{
		if (bul->GetBulletType() >= 0&& bul->GetBulletType() < 4)
		//if (bul->GetBulletType() == 0)
		{
			for (auto& enemy : GetEnemyAList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < bul->GetPlayerBulSize())
					{
						bul->SetAlive(false);

						if (bul->GetBulletType() == PlayerRed)
						{
							enemy->SetFlg(false);
							m_WaveEnemyNum--;
						}
					}
				}
			}

			for (auto& enemy : GetEnemyBList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < bul->GetPlayerBulSize())
					{
						bul->SetAlive(false);

						if (bul->GetBulletType() == PlayerBlue)
						{
							enemy->SetFlg(false);
							m_WaveEnemyNum--;
						}
					}
				}
			}

			for (auto& enemy : GetEnemyCList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < bul->GetPlayerBulSize())
					{
						bul->SetAlive(false);

						if (bul->GetBulletType() == PlayerYellow)
						{
							enemy->SetFlg(false);
							m_WaveEnemyNum--;
						}
					}
				}
			}

			for (auto& enemy : GetEnemyDList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < bul->GetPlayerBulSize())
					{
						bul->SetAlive(false);

						if (bul->GetBulletType() == PlayerGreen)
						{
							enemy->SetFlg(false);
							m_WaveEnemyNum--;
						}
					}
				}
			}
		}
	}
}

void Scene::FunnelBul_Enemy()
{
	for (auto& bul : m_bulletList)
	{
		if (bul->GetBulletType() == 8)
		{
			for (auto& enemy : GetEnemyAList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < 32)
					{
						bul->SetAlive(false);

						enemy->SetFlg(false);

						m_WaveEnemyNum--;
					}
				}
			}

			for (auto& enemy : GetEnemyBList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < 32)
					{
						bul->SetAlive(false);

						enemy->SetFlg(false);

						m_WaveEnemyNum--;
					}
				}
			}

			for (auto& enemy : GetEnemyCList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < 32)
					{
						bul->SetAlive(false);

						enemy->SetFlg(false);

						m_WaveEnemyNum--;
					}
				}
			}

			for (auto& enemy : GetEnemyDList())
			{
				if (enemy->GetFlg())
				{
					Math::Vector2 v;
					v = enemy->GetPos() - bul->GetPos();

					if (v.Length() < 32)
					{
						bul->SetAlive(false);

						enemy->SetFlg(false);

						m_WaveEnemyNum--;
					}
				}
			}
		}
	}
}

void Scene::EnemyBul_Player()
{
	if (m_player.GetFlg())
	{
		for (auto& bul : m_bulletList)
		{
			if (bul->GetBulletType() >= 4 && bul->GetBulletType() < 8)//とりあえずプレイヤーかファンネルの弾以外
			{

				Math::Vector2 v;
				v = bul->GetPos() - m_player.GetPos();

				if (v.Length() < bul->GetEnemyBulSize())
				{
					m_player.SetHp(m_player.GetHp() - 1);
					bul->SetAlive(false);
				}
			}
		}
	}
}

void Scene::Pause(bool a_pause)
{
	m_pauseFlg = a_pause;
}

void Scene::Update()
{
	switch (nowScene)
	{
	case SceneType::Title:
		UpdateTitle();
		break;
	case SceneType::Game:
		UpdateGame();
		break;
	case SceneType::Result:
		UpdateResult();
		break;
	default:
		break;
	}

}

void Scene::Init()
{
	srand(timeGetTime());
	
	InitTitle();
	
	InitGame();
	
	InitResult();

	m_pauseFlg = false;

	//画像読み込み

	m_ChangeBlackTex.Load("Texture/Back/blind.png");
	m_PushEnterTex.Load("Texture/Title/push_enter.png");
	m_RankTex.Load("Texture/UI/rank.png");
	m_GameOverTex.Load("Texture/UI/gameover.png");

	//自機
	//m_playerTex.Load("Texture/demo_jet.png");
	//m_player.SetTexture(&m_playerTex);
	m_hit.SetPlayer(&m_player);

	m_player.SetOwner(this);
	//m_enemyA[0]->SetOwner(this);
	m_hit.SetOwner(this);

	//弾
	/*m_pA_BulTex.Load("Texture/demo_bullet.png");
	m_player.SetBulletTexture(&m_pA_BulTex);
	m_pB_BulTex.Load("Texture/demo_bullet2.png");
	m_player.SetBulletTexture(&m_pB_BulTex);*/
	
	//m_pBulletTex[0].Load("Texture/demo_bullet.png");
	//m_player.SetBulletTexture(&m_pBulletTex[0]);
	//m_pBulletTex[1].Load("Texture/demo_bullet2.png");
	//m_enemyA[0]->SetBulletTexture(&m_pBulletTex[1]);

	//ステータス
	//m_statusTex.Load("Texture/UI/status.png");
	//m_status.SetTexture(&m_statusTex);

	Debug1 = 0;
	Debug2 = 0;
	Debug3 = {};
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("time : %d", m_Time);
		ImGui::Text("abi2 : %d", Debug2);
		ImGui::Text("EnemyNum : %d", m_WaveEnemyNum);

		ImGui::Text("abi : %d", pa);
		ImGui::Text("abi : %d", pb);
		ImGui::Text("abi : %d", pc);
		ImGui::Text("abi : %d", pd);
		ImGui::Text("abi : %d", pe);
	}
	ImGui::End();
}
