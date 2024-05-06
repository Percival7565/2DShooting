#include "../Scene/Scene.h"
#include "Number.h"

void C_Number::Init()
{
	m_NumberTex.Load("Texture/UI/num.png");
}

void C_Number::Update()
{
}

void C_Number::DrawLeft(int x, Math::Vector2 num_Pos)
{
	int z;
	z = std::to_string(x).length();

	d_num[0] = x / 1000000;//•S–œ

	x -= d_num[0] * 1000000;

	d_num[1] = x / 100000;//\–œ

	x -= d_num[1] * 100000;

	d_num[2] = x / 10000;//ˆê–œ

	x -= d_num[2] * 10000;

	d_num[3] = x / 1000;//ç

	x -= d_num[3] * 1000;

	d_num[4] = x / 100;//•S

	x -= d_num[4] * 100;

	d_num[5] = x / 10;//\

	x -= d_num[5] * 10;

	d_num[6] = x;//ˆê

	zeroFlg = false;

	for (int i = 0; i < Max_digit; i++)
	{
		if (d_num[i] > 0)
		{
			zeroFlg = true;
		}

		if (zeroFlg)
		{
			Math::Matrix l_mat = Math::Matrix::CreateTranslation(num_Pos.x + i * 42 - (Max_digit - z) * 42, num_Pos.y, 0);
			DrawImg(l_mat, &m_NumberTex, Math::Rectangle(d_num[i] * 42, 0, 42, 50), 1.0f);
		}
	}
}

void C_Number::DrawRight(int x, Math::Vector2 num_Pos)
{
	d_num[0] = x / 1000000;//•S–œ

	x -= d_num[0] * 1000000;

	d_num[1] = x / 100000;//\–œ

	x -= d_num[1] * 100000;

	d_num[2] = x / 10000;//ˆê–œ

	x -= d_num[2] * 10000;

	d_num[3] = x / 1000;//ç

	x -= d_num[3] * 1000;

	d_num[4] = x / 100;//•S

	x -= d_num[4] * 100;

	d_num[5] = x / 10;//\

	x -= d_num[5] * 10;

	d_num[6] = x;//ˆê

	zeroFlg = false;

	for (int i = 0; i < Max_digit; i++)
	{
		if (d_num[i] > 0)
		{
			zeroFlg = true;
		}

		if (zeroFlg)
		{
			Math::Matrix l_mat = Math::Matrix::CreateTranslation(num_Pos.x + i * 42 , num_Pos.y, 0);
			DrawImg(l_mat, &m_NumberTex, Math::Rectangle(d_num[i] * 42, 0, 42, 50),1.0f );
		}
	}
}

void C_Number::DrawWaveNum(int x, Math::Vector2 num_Pos, float alpha, Math::Vector2 num_Sc, float add_PosX)
{
	int z;
	z = std::to_string(x).length();

	d_num[0] = x / 1000000;//•S–œ

	x -= d_num[0] * 1000000;

	d_num[1] = x / 100000;//\–œ

	x -= d_num[1] * 100000;

	d_num[2] = x / 10000;//ˆê–œ

	x -= d_num[2] * 10000;

	d_num[3] = x / 1000;//ç

	x -= d_num[3] * 1000;

	d_num[4] = x / 100;//•S

	x -= d_num[4] * 100;

	d_num[5] = x / 10;//\

	x -= d_num[5] * 10;

	d_num[6] = x;//ˆê

	zeroFlg = false;

	for (int i = 0; i < Max_digit; i++)
	{
		if (d_num[i] > 0)
		{
			zeroFlg = true;
		}

		if (zeroFlg)
		{
			Math::Matrix s_mat = Math::Matrix::CreateScale(num_Sc.x, num_Sc.y, 0);
			//Math::Matrix t_mat = Math::Matrix::CreateTranslation(num_Pos.x + i * 42 - (Max_digit - z) * 42, num_Pos.y, 0);
			Math::Matrix t_mat = Math::Matrix::CreateTranslation(num_Pos.x + i * 42  - ((Max_digit - z) * 42 ) + add_PosX, num_Pos.y, 0);
			Math::Matrix mat = s_mat * t_mat;
			DrawImg(mat, &m_NumberTex, Math::Rectangle(d_num[i] * 42, 0, 42, 50), alpha);
		}
	}
}
