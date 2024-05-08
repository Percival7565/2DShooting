#pragma once

#include "Utility.h"

#include "../Texture/Back.h"
#include "../Texture/Title.h"

#include "../Player/Player.h"

//#include "../Attack/Bullet.h"//していいのか？？？

//#include "../Enemy/BaseEnemy.h"
#include "../Enemy/EnemyA/EnemyA.h"

#include "../Attack/Hit.h"

#include "../Player/Status.h"
#include "../Texture/Wave.h"
#include "../Texture/Number.h"
#include "../Player/Ability.h"



enum SceneType
{
	Title,
	Game,
	Result
};

class Scene
{
private:

	C_Back m_back;
	C_Title m_title;

	C_Player m_player;
	std::vector<std::shared_ptr<C_EnemyA>> m_enemyAList;
	C_Hit m_hit;
	C_Status m_status;
	C_Wave m_wave;
	C_Number m_number;
	C_Ability m_ability;

	std::vector<std::shared_ptr<C_Bullet>> m_bulletList;
	
	// 行列 ・・・ 座標などの情報
	Math::Matrix matrix;

	SceneType nowScene;

	//タイトル
	int m_TitleCnt;
	bool m_SceneChange;
	KdTexture m_ChangeBlackTex;
	Math::Matrix m_BlackMat;
	float m_BlackAlpha;
	float m_TitleOutAlphaA;
	float m_TitleOutAlphaB;

	//ゲーム
	int m_GameFlow;
	int m_GameFrame;

	int m_WaveEnemyNum;

	int m_EnemyFrame;

	int m_NowWave;
	

	bool keyFlg;

	bool m_pauseFlg;

	KdTexture m_playerTex;
	/*KdTexture m_pA_BulTex;
	KdTexture m_pB_BulTex;*/
	//KdTexture m_pBulletTex[10];
	KdTexture m_enemyTex;
	KdTexture m_statusTex;

	//フレーム数
	int frame;

	int Debug1;
	int Debug2;
	int Debug3;

	

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
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

	void MakeEnemyA();

	void PlayerBul_Enemy();
	void EnemyBul_Player();

	void Pause(bool a_pause);

	void SetDebug1(int a_Debug) { Debug1 = a_Debug; }
	void SetDebug2(int a_Debug) { Debug2 = a_Debug; }
	void SetDebug3(int a_Debug) { Debug3 = a_Debug; }

	//ゲッター
	C_Player* GetPlayer() { return &m_player; }
	//C_BaseEnemy* GetEnemy() { return &m_enemy; }
	

	// GUI処理
	void ImGuiUpdate();

	void AddBullet(std::shared_ptr<C_Bullet> a_bul)
	{
		m_bulletList.push_back(a_bul);
	}

	std::vector<std::shared_ptr<C_EnemyA>> GetEnemyAList()
	{
		return m_enemyAList;
	}

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
