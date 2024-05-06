#pragma once

class C_Title
{
public:
	C_Title() {}
	~C_Title() {}

	void Init();
	void Update();
	void Draw();
private:

	int frame;

	//ƒm[ƒ}ƒ‹
	KdTexture m_neonATex;
	Math::Vector2 m_neonAPos;
	Math::Matrix m_neonAMat;

	float m_Aalpha;

	//–¾‚é‚¢
	KdTexture m_neonBTex;
	Math::Vector2 m_neonBPos;
	Math::Matrix m_neonBMat;

	float m_Balpha;

	//O–³‚µ
	/*KdTexture m_neonCTex;
	Math::Vector2 m_neonCPos;
	Math::Matrix m_neonCMat;*/

	//“®‚«‚ğ‚Â‚¯‚é
	int m_neonTake;
	int m_angle;
};