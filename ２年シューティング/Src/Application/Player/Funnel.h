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

	KdTexture m_Tex;	//�摜
	Math::Vector2 m_pos;//���W
	Math::Matrix m_mat;	//�s��

};