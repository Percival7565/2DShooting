#pragma once

#include "Utility.h"

#include "../Player/Player.h"

//#include "../Enemy/BaseEnemy.h"
#include "../Enemy/EnemyA/EnemyA.h"

#include "../Attack/Hit.h"

#include "../Player/Status.h"

enum SceneType
{
	Title,
	Game,
	Result
};

class Scene
{
private:

	C_Player m_player;
	std::vector<std::shared_ptr<C_EnemyA>> m_enemyAList;
	C_Hit m_hit;
	C_Status m_status;
	
	// �s�� �E�E�E ���W�Ȃǂ̏��
	Math::Matrix matrix;

	SceneType nowScene;
	//�^�C�g��
	float titleX;
	float titleY;
	Math::Color TitleColor;

	float gameX;
	float gameY;

	//���U���g
	float resultX;
	float resultY;

	bool keyFlg;

	KdTexture m_playerTex;
	/*KdTexture m_pA_BulTex;
	KdTexture m_pB_BulTex;*/
	KdTexture m_pBulletTex[10];
	KdTexture m_enemyTex;
	KdTexture m_statusTex;

	//�t���[����
	int frame;

public:

	// �����ݒ�
	void Init();

	// ���
	void Release();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw2D();

	void DrawTitle();
	void UpdateTitle();
	void InitTitle();

	void DrawGame();
	void UpdateGame();
	void InitGame();

	void DrawResult();
	void UpdateResult();
	void InitResult();

	//�Q�b�^�[
	C_Player* GetPlayer() { return &m_player; }
	//C_BaseEnemy* GetEnemy() { return &m_enemy; }

	// GUI����
	void ImGuiUpdate();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
