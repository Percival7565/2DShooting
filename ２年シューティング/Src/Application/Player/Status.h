#pragma once

class Scene;

class C_Status
{
public:
	
	void Init();
	void Update();
	void Draw();

	//void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:

	KdTexture m_stTex;	//‰æ‘œ
	Math::Vector2 m_pos;//À•W
	Math::Matrix m_mat;	//s—ñ

	bool m_bFlg;

};

