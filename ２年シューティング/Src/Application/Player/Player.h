#pragma once
#include "Funnel.h"
//#include "../Attack/Bullet.h"

class Scene;

class C_Player
{
public:

	void Init();
	void Update();
	void Draw();

	//void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex;}
	//void SetBulletTexture(KdTexture* a_pTex) { m_pBulletTex = a_pTex; }
	void SetFlg(bool a_bFlg) { m_bFlg = a_bFlg; }

	void SetAbility(int a_abi) { m_abi = a_abi; }
	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetPause(bool a_pause) { m_playerPauseFlg = a_pause; }

	Math::Vector2 GetPos() { return m_pos; }
	bool GetFlg() { return m_bFlg; }
	HitStruct GetObj();
	bool GetZero() { return m_zero; }

	int GetBulletSize() { return m_plusbulSize; }
private:

	int frame;
	int frame2;
	int frame3;

	KdTexture m_playerTex;	//画像
	KdTexture m_C_kasanTex;	//画像
	Math::Vector2 m_pos;//座標
	Math::Matrix m_mat;	//行列
	bool m_bFlg;

	KdTexture m_BulletTex;	//画像

	int m_playerAnimeCnt;
	bool m_playerUpFlg;
	int m_UpAnimeCnt;
	bool m_playerDownFlg;
	int m_DownAnimeCnt;

	//std::vector<C_Bullet*> m_bulletList;
	
	//アビリティ用
	static const int abilityMax = 5;
	int m_ability[abilityMax];
	bool m_abilityUseFlg[abilityMax];

	bool m_UseFlg;
	bool m_playerPauseFlg;

	int m_plusbullet;
	int m_plusbulSize;
	int m_plusbulSpeed;
	int m_bulSpeed;

	int m_abi;

	int m_zero = 0;

	C_Funnel m_funnel;

	Scene* m_pOwner;

};

