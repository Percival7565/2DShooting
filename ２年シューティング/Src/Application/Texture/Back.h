#pragma once

class C_Back
{
public:
	C_Back() { Init(); }
	~C_Back() {}

	void Init();
	void Update();
	void Draw();

private:

	static const int m_backNum = 2;
	
	//Blind
	KdTexture m_blindTex;//posやmatはスカイと共用

	//Sky
	KdTexture m_skyTex;
	Math::Vector2 m_skyPos;
	Math::Matrix m_skyMat;

	//BackA
	KdTexture m_backATex;
	Math::Vector2 m_aPos[m_backNum];
	Math::Matrix m_aMat[m_backNum];

	//BackB
	KdTexture m_backBTex;
	Math::Vector2 m_bPos[m_backNum];
	Math::Matrix m_bMat[m_backNum];

};
