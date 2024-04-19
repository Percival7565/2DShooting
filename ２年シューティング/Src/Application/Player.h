#pragma once
#include "Bullet.h"

class Scene;

class C_Player
{
public:

	void Init();
	void Update();
	void Draw();

	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex;}
	void SetBulletTexture(KdTexture* a_pTex) { m_pBulletTex = a_pTex; }
	void SetFlg(bool a_bFlg) { m_bFlg = a_bFlg; }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	Math::Vector2 GetPos() { return m_pos; }
	bool GetFlg() { return m_bFlg; }
	HitStruct GetObj();
private:

	int frame;

	KdTexture* m_pTex;	//âÊëú
	Math::Vector2 m_pos;//ç¿ïW
	Math::Matrix m_mat;	//çsóÒ
	bool m_bFlg;

	KdTexture* m_pBulletTex;	//âÊëú

	std::vector<C_Bullet*> m_bulletList;

	Scene* m_pOwner;

};

