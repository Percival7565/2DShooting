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

	KdTexture m_stTex;	//�摜
	Math::Vector2 m_pos;//���W
	Math::Matrix m_mat;	//�s��

	bool m_bFlg;

};

