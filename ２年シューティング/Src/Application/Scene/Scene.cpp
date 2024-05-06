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
			InitGame();
			nowScene = SceneType::Game;
		}
	}
	else
	{
		keyFlg = false;
	}
	/*if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		titleX = titleX + 10;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		titleX = titleX - 10;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		titleY = titleY + 10;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		titleY = titleY - 10;
	}*/
}

void Scene::InitTitle()
{
	m_title.Init();
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
}

void Scene::UpdateGame()
{
	m_back.Update();

	//デバッグ
	if (GetAsyncKeyState('P') & 0x8000)
	{
		Pause(true);
	}
	else
	{
		Pause(false);
	}

	if (!m_pauseFlg)
	{
		//デバッグ
		if (GetAsyncKeyState('E') & 0x8000)
		{
			std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
			tempEnemy->SetOwner(this);
			tempEnemy->Init();
			//tempEnemy->SetPos({ 0.0f + (rand()%10 * 100),-200.0f });
			tempEnemy->SetPos({ 500.0f,-200.0f });
			m_enemyAList.push_back(tempEnemy);
		}

		m_player.Update();
		for (auto& enemyA : m_enemyAList)
		{
			enemyA->Update();
		}
		m_status.Update();

		PlayerBul_Enemy();//プレイヤーの弾と敵本体の当たり判定
		EnemyBul_Player();//敵の弾とプレイヤー本体の当たり判定

		m_hit.GetHitJet();

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



		for (int b = 0; b < m_bulletList.size(); b++)
		{
			m_bulletList[b]->Update();
		}

		//可変長配列をポインタ操作するイテレーター（リモコン）
		//イテレーターは毛偏重配列のアドレスを格納できる

		std::vector<std::shared_ptr<C_Bullet>>::iterator it;	// 可変長配列

		it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納

		while (it != m_bulletList.end())
		{
			const bool bAlive = (*it)->GetAlive();
			if (!bAlive)
			{
				//delete (*it);
				it = m_bulletList.erase(it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
			}
			else
			{
				it++;
			}
		}
	}
	m_wave.Update();
}

void Scene::InitGame()
{
	m_player.Init();

	m_status.Init();

	m_wave.Init();
	//m_enemyA[0]->Init();

	for (int i = 0; i < 10; i++)
	{
		//C_EnemyA* enemyA = new C_EnemyA();
		std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
		tempEnemy->SetOwner(this);
		tempEnemy->Init();
		tempEnemy->SetPos({ -300.0f + (i * 100.0f),200.0f});
		//tempEnemy->SetPos({0,0});
		m_enemyAList.push_back(tempEnemy);
	}
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

void Scene::PlayerBul_Enemy()
{
	for (auto& bul : m_bulletList)
	{
		if (bul->GetBulletType()== 0)
		{
			for (auto& enemy : GetEnemyAList())
			{
				Math::Vector2 v;
				v = enemy->GetPos() - bul->GetPos();

				if (v.Length() < 16.0f)
				{
					bul->SetAlive(false);

					enemy->SetFlg(false);
				}

			}
		}
	}
}

void Scene::EnemyBul_Player()
{
	for (auto& bul : m_bulletList)
	{
		if (bul->GetBulletType() > 0)//とりあえずプレイヤーの基本の弾以外
		{
			
			Math::Vector2 v;
			v = bul->GetPos() - m_player.GetPos();

			if (v.Length() < 16.0f)
			{
				m_player.SetFlg(false);
				bul->SetAlive(false);
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
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
