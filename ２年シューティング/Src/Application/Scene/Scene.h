#pragma once

#include "Utility.h"

#include "../Texture/Back.h"
#include "../Texture/Title.h"

#include "../Player/Player.h"

//#include "../Attack/Bullet.h"//していいのか？？？

//#include "../Enemy/BaseEnemy.h"
#include "../Enemy/EnemyA/EnemyA.h"
#include "../Enemy/EnemyB/EnemyB.h"
#include "../Enemy/EnemyC/EnemyC.h"
#include "../Enemy/EnemyD/EnemyD.h"

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
	std::vector<std::shared_ptr<C_EnemyB>> m_enemyBList;
	std::vector<std::shared_ptr<C_EnemyC>> m_enemyCList;
	std::vector<std::shared_ptr<C_EnemyD>> m_enemyDList;
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

	KdTexture m_PushEnterTex;
	Math::Matrix m_PushMat;
	float m_pushAlpha;

	KdTexture m_RankTex;
	Math::Matrix m_RankMat;
	Math::Matrix m_RankSMat;
	Math::Matrix m_RankTMat;
	int m_rank;
	float m_rankAlpha;

	//ゲーム
	int m_GameFlow;
	int m_GameFrame;

	int m_WaveEnemyNum;

	int m_EnemyFrame;

	int m_NowWave;
	bool m_WavePlusFlg;

	bool keyFlg;

	bool m_pauseFlg;

	int m_Time;
	int m_TimeMinutes;
	int m_Timeframe;

	//リザルト
	KdTexture m_GameOverTex;
	Math::Matrix m_GameOverMat;
	int resultframe;

	//フレーム数
	int frame;
	int frame2;
	int frame3;

	int Debug1;
	float Debug2;
	Math::Vector2 Debug3;

	

public:

	int pa = 0;
	int pb = 0;
	int pc = 0;
	int pd = 0;
	int pe = 0;

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

	void MakeEnemyA(Math::Vector2 a_pos,int a_type);
	void MakeEnemyB(Math::Vector2 a_pos, int a_type);
	void MakeEnemyC(Math::Vector2 a_pos, int a_type);
	void MakeEnemyD(Math::Vector2 a_pos, int a_type);

	void PlayerBul_EnemyA();
	void FunnelBul_Enemy();
	void EnemyBul_Player();

	void Pause(bool a_pause);

	void SetEnemyNum(int a_num) { m_WaveEnemyNum = a_num; }

	int GetEnemyNum() { return m_WaveEnemyNum; }

	void SetDebug1(int a_Debug) { Debug1 = a_Debug; }
	void SetDebug2(int a_Debug) { Debug2 = a_Debug; }
	void SetDebug3(Math::Vector2 a_Debug) { Debug3 = a_Debug; }

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

	std::vector<std::shared_ptr<C_EnemyB>> GetEnemyBList()
	{
		return m_enemyBList;
	}

	std::vector<std::shared_ptr<C_EnemyC>> GetEnemyCList()
	{
		return m_enemyCList;
	}

	std::vector<std::shared_ptr<C_EnemyD>> GetEnemyDList()
	{
		return m_enemyDList;
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
