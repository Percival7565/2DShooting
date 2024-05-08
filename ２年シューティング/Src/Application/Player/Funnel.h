#pragma once

class C_Funnel
{
public:
	C_Funnel(){}
	~C_Funnel(){}

	void Init();
	void Update();
	void Draw();

private:

	KdTexture m_Tex;	//‰æ‘œ
	Math::Vector2 m_pos;//À•W
	Math::Matrix m_mat;	//s—ñ

};