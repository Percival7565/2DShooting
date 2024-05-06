#pragma once

class C_Number
{
public:
	C_Number() { Init(); }
	~C_Number() {}
	
	void Init();
	void Update();
	void DrawLeft(int x, Math::Vector2 num_Pos);
	void DrawRight(int x, Math::Vector2 num_Pos);
	void DrawWaveNum(int x, Math::Vector2 num_Pos,float alpha ,Math::Vector2 num_Sc,float add_PosX);
private:

	//”š•¶š—ñ•\¦
	KdTexture m_NumberTex;
	static const int Max_digit = 7;
	int d_num[Max_digit];
	bool zeroFlg;

};
