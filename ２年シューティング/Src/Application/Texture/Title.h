#pragma once

class C_Title
{
public:
	C_Title() {}
	~C_Title() {}

	void Init();
	void Update();
	void Draw();

	void SetAalpha(int a_Aalpha) { m_Aalpha = a_Aalpha; }
	void SetBalpha(int a_Balpha) { m_Balpha = a_Balpha; }

	void SetTakeFlg(bool a_Flg) { m_TakeFlg = a_Flg; }

	float GetAalpha() { return m_Aalpha; }
	float GetBalpha() { return m_Balpha; }


private:

	int frame;

	//ÉmÅ[É}Éã
	KdTexture m_neonATex;
	Math::Vector2 m_neonAPos;
	Math::Matrix m_neonAMat;

	float m_Aalpha;

	//ñæÇÈÇ¢
	KdTexture m_neonBTex;
	Math::Vector2 m_neonBPos;
	Math::Matrix m_neonBMat;

	float m_Balpha;
	float m_Bsinalpha;


	//Oñ≥Çµ
	/*KdTexture m_neonCTex;
	Math::Vector2 m_neonCPos;
	Math::Matrix m_neonCMat;*/

	//ìÆÇ´ÇÇ¬ÇØÇÈ
	int m_neonTake;
	int m_angle;

	bool m_TakeFlg;
};