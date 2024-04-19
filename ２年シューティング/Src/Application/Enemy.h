#pragma once
#include "Bullet.h"

class Scene;

class C_Enemy
{
public:

	void Init();
	void Update();
	void Draw();

	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetBulletTexture(KdTexture* a_pTex) { m_pB_BulTex = a_pTex; }
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetFlg(bool a_bFlg) { m_bFlg = a_bFlg; }

	Math::Vector2 GetPos() { return m_pos; }
	bool GetFlg() { return m_bFlg; }
	HitStruct GetObj();
private:

	int frame;

	KdTexture* m_pTex;	//画像
	Math::Vector2 m_pos;//座標
	Math::Matrix m_mat;	//行列
	Math::Matrix m_tmat;	//行列
	Math::Matrix m_smat;	//行列
	bool m_bFlg;			//生死

	KdTexture* m_pB_BulTex;	//画像

	std::vector<C_Bullet*> m_bulletList;

	Scene* m_pOwner;

	//お試し
	int angle;
};