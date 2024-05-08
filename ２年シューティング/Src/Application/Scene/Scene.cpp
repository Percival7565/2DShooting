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
	
	//SHADER.m_spriteShader.DrawString(titleX, titleY, "タイトル画面", Math::Vector4(1, 1, 0, 1));
}

void Scene::UpdateTitle()
{
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

	m_BlackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void Scene::InitTitle()
{
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

	m_player.Draw();
	for (auto& enemyA : m_enemyAList)
	{
		enemyA->Draw();
	}

	m_status.Draw();

	for (auto& bullet : m_bulletList)
	{
		bullet->Draw();
	}

	m_wave.Draw();
	//デバッグ
	//m_number.DrawLeft(123456,{0,0});
	m_ability.Draw();

	DrawImg(m_BlackMat, &m_ChangeBlackTex, { 0,0,1280,720 }, m_BlackAlpha);
}

void Scene::UpdateGame()
{
	
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
			m_player.SetPos({ -500,0 });
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

		if (m_EnemyFrame >= 100)
		{
			//デバッグ
			//if (GetAsyncKeyState('E') & 0x8000)
			{
				MakeEnemyA();
			}
		}
		else
		{
			m_EnemyFrame++;
		}

		//プレイヤーももともとここにいた
		m_ability.Update();
		

		for (auto& enemyA : m_enemyAList)
		{
			enemyA->Update();
		}
		m_status.Update();

		PlayerBul_Enemy();//プレイヤーの弾と敵本体の当たり判定
		EnemyBul_Player();//敵の弾とプレイヤー本体の当たり判定

		m_hit.GetHitJet();


		for (int b = 0; b < m_bulletList.size(); b++)
		{
			m_bulletList[b]->SetPlayerBulSizeLv(m_player.GetBulletSize());
			m_bulletList[b]->Update();
		}


		break;
	case 2:
		
		break;
	default:
		break;
	}

	
	m_player.SetAbility(m_ability.GetSelectAbi());
	m_player.Update();
	if (m_player.GetZero())
	{
		m_ability.SetGetAbi(0);
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
	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
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
	}

	m_BlackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void Scene::InitGame()
{
	m_NowWave = 0;

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
	SHADER.m_spriteShader.DrawString(0,0, "リザルト画面", Math::Vector4(1, 1, 0, 1));
}

void Scene::UpdateResult()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
			InitTitle();
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
}

void Scene::MakeEnemyA()
{
	std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
	m_WaveEnemyNum++;
	m_EnemyFrame = 0;
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	//tempEnemy->SetPos({ 0.0f + (rand()%10 * 100),-200.0f });
	tempEnemy->SetPos({ 500.0f,-200.0f });
	m_enemyAList.push_back(tempEnemy);
}

void Scene::PlayerBul_Enemy()
{
	for (auto& bul : m_bulletList)
	{
		if (bul->GetBulletType()== 0)
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
			if (bul->GetBulletType() > 0)//とりあえずプレイヤーの基本の弾以外
			{

				Math::Vector2 v;
				v = bul->GetPos() - m_player.GetPos();

				if (v.Length() < bul->GetEnemyBulSize())
				{
					m_player.SetFlg(false);
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
	Debug3 = 0;
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("ABI0 : %d", Debug1);
		ImGui::Text("ABI1 : %d", Debug2);
		ImGui::Text("EnemyNum : %d", m_WaveEnemyNum);
	}
	ImGui::End();
}
