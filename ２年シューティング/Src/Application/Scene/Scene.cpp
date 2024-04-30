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

	// ������������͂ق��̕`�悪�I����Ă��珑�����ƁI������
	// ������\��
	//SHADER.m_spriteShader.DrawString(640 - 340, 360 - 10, "�x�[�X�v���O����", Math::Vector4(0, 0, 0, frame / (60.0f * 10) ));
	//SHADER.m_spriteShader.DrawString(640 - 344, 360 - 14, "�x�[�X�v���O����", Math::Vector4(1, 1, 0, frame / (60.0f * 10) ));

}

void Scene::DrawTitle()
{
	
	SHADER.m_spriteShader.DrawString(titleX, titleY, "�^�C�g�����", Math::Vector4(1, 1, 0, 1));
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
	for (auto& enemyA : m_enemyAList)
	{
		enemyA->Draw();
	}
	m_status.Draw();
}

void Scene::UpdateGame()
{
	m_player.Update();
	for (auto& enemyA : m_enemyAList)
	{
		enemyA->Update();
	}
	m_status.Update();

	for (int i = 0; i < m_enemyAList.size(); i++)
	{
		if (m_hit.GetHitJet(m_player.GetObj(), m_enemyAList[i]->GetObj()))
		{
			m_player.SetFlg(false);
			m_enemyAList[i]->SetFlg(false);
		}
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
	//m_enemyA[0]->Init();
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

	
	//C_EnemyA* enemyA = new C_EnemyA();
	std::shared_ptr<C_EnemyA> tempEnemy = std::make_shared<C_EnemyA>();
	tempEnemy->SetOwner(this);
	tempEnemy->Init();
	tempEnemy->SetPos({ 0,200 });
	m_enemyAList.push_back(tempEnemy);

	//�摜�ǂݍ���

	//���@
	m_playerTex.Load("Texture/demo_jet.png");
	m_player.SetTexture(&m_playerTex);

	m_player.SetOwner(this);
	//m_enemyA[0]->SetOwner(this);
	m_hit.SetOwner(this);

	//�e
	/*m_pA_BulTex.Load("Texture/demo_bullet.png");
	m_player.SetBulletTexture(&m_pA_BulTex);
	m_pB_BulTex.Load("Texture/demo_bullet2.png");
	m_player.SetBulletTexture(&m_pB_BulTex);*/
	
	m_pBulletTex[0].Load("Texture/demo_bullet.png");
	m_player.SetBulletTexture(&m_pBulletTex[0]);
	//m_pBulletTex[1].Load("Texture/demo_bullet2.png");
	//m_enemyA[0]->SetBulletTexture(&m_pBulletTex[1]);

	//�X�e�[�^�X
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

	// �f�o�b�O�E�B���h�E
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
