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
	
	SHADER.m_spriteShader.DrawString(titleX, titleY, "タイトル画面", Math::Vector4(1, 1, 0, 1));
}

void Scene::UpdateTitle()
{
	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
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
}

void Scene::DrawGame()
{
	m_player.Draw();
	m_enemy.Draw();
	m_status.Draw();
}

void Scene::UpdateGame()
{
	m_player.Update();
	m_enemy.Update();
	m_status.Update();

	if (m_hit.GetHitJet(m_player.GetObj(),m_enemy.GetObj()))
	{
		m_player.SetFlg(false);
		m_enemy.SetFlg(false);
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
			nowScene = SceneType::Result;
		}
	}
	else
	{
		keyFlg = false;
	}
}

void Scene::InitGame()
{
	m_player.Init();
	m_enemy.Init();
}

void Scene::DrawResult()
{
}

void Scene::UpdateResult()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == false)
		{
			keyFlg = true;
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
	
	InitTitle();
	
	InitGame();
	
	InitResult();


	//画像読み込み

	//自機
	m_playerTex.Load("Texture/demo_jet.png");
	m_player.SetTexture(&m_playerTex);

	m_player.SetOwner(this);
	m_enemy.SetOwner(this);
	m_hit.SetOwner(this);

	//弾
	/*m_pA_BulTex.Load("Texture/demo_bullet.png");
	m_player.SetBulletTexture(&m_pA_BulTex);
	m_pB_BulTex.Load("Texture/demo_bullet2.png");
	m_player.SetBulletTexture(&m_pB_BulTex);*/
	
	m_pBulletTex[0].Load("Texture/demo_bullet.png");
	m_player.SetBulletTexture(&m_pBulletTex[0]);
	m_pBulletTex[1].Load("Texture/demo_bullet2.png");
	m_enemy.SetBulletTexture(&m_pBulletTex[1]);

	//敵
	m_enemyTex.Load("Texture/demo_enemy.png");
	m_enemy.SetTexture(&m_enemyTex);

	//ステータス
	m_statusTex.Load("Texture/status.png");
	m_status.SetTexture(&m_statusTex);
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
