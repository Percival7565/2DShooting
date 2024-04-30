#pragma once
#include "../Scene/Utility.h"	//応急処置
#include "../Attack/Bullet.h"

class Scene;

class C_BaseEnemy
{
public:

	C_BaseEnemy() {}
	~C_BaseEnemy() {}

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }
	//void SetBulletTexture(KdTexture* a_pTex) { m_B_BulTex = a_pTex; }
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetFlg(bool a_bFlg) { m_bFlg = a_bFlg; }
	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }

	Math::Vector2 GetPos() { return m_pos; }
	bool GetFlg() { return m_bFlg; }
	HitStruct GetObj();

protected:

	int frame;

	KdTexture m_tex;	//画像
	Math::Vector2 m_pos;//座標
	Math::Matrix m_mat;		//行列
	Math::Matrix m_tmat;	//行列
	Math::Matrix m_smat;	//行列
	bool m_bFlg;			//生死

	KdTexture m_B_BulTex;	//画像

	std::vector<C_Bullet*> m_bulletList;

	Scene* m_pOwner;

	std::shared_ptr<C_Bullet> tempBullet;

	//お試し
	int angle;
};