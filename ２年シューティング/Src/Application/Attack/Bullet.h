#pragma once

class C_Bullet
{
public:
	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//発射処理
	void Shot(Math::Vector2 a_shotPos,int BulletType,Math::Vector2 a_targetPos,float a_bulSpeed);	//発射処理のオーバーライド

	const bool GetAlive();
	const Math::Vector2 GetPos();

	int GetBulletType() { return m_bulletType; }
	float GetEnemyBulSize() { return enemyBulSize; }
	float GetPlayerBulSize() { return playerBulSize; }

	//セッター
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetColor(int a_color) { m_PlayerColor = a_color; }
	void SetEnemyColor(int a_Ecolor) { m_EnemyColor = a_Ecolor; }

	void SetAlive(bool a_bAlive) { m_bAlive = a_bAlive; }

	void SetPlayerBulSize(float a_PbulSize) { playerBulSize = a_PbulSize; }//多分使わん
	void SetPlayerBulSizeLv(int a_PbulSizeLevel) { playerBulSizeLv = a_PbulSizeLevel; }

private:
	KdTexture* m_pTex;		
	Math::Vector2 m_pos;	
	Math::Vector2 m_size;	
	Math::Matrix m_tmat;		
	Math::Matrix m_smat;		
	Math::Matrix m_mat;		
	Math::Matrix m_enemyMat;
	bool m_bAlive;

	Math::Vector2 m_move;	//移動量

	const float TEX_RADIUS = 8.0f;	//半径

	int m_bulletType;
	int m_PlayerColor;
	int m_EnemyColor;

	KdTexture m_kasanTex;

	float enemyBulSize;
	float playerBulSize;
	int playerBulSizeLv;
};