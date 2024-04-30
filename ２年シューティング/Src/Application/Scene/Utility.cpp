#include "Utility.h"

void DrawImg(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, float a_alpha)
{
	SHADER.m_spriteShader.SetMatrix(a_mat);
	SHADER.m_spriteShader.DrawTex(a_tex, a_rect, a_alpha);
}

void DrawImgEX(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, Math::Color a_color)
{
	SHADER.m_spriteShader.SetMatrix(a_mat);
	Math::Rectangle srcRect = a_rect;
	SHADER.m_spriteShader.DrawTex(a_tex, 0, 0, &srcRect, &a_color);
}

void DrawMaru(float x, float y, float rad, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawCircle(x, y, rad, color, nuri);
}

void DrawSankaku(float x1, float y1, float x2, float y2, float x3, float y3, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawTriangle(x1, y1, x2, y2, x3, y3, color, nuri);
}

void DrawHako(float x, float y, float xs, float ys, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawBox(x, y, xs, ys, color, nuri);
}

void DrawSen(float x, float y, float xx, float yy, Math::Color* color)
{
	SHADER.m_spriteShader.DrawLine(x, y, xx, yy, color);
}

void DrawTen(float x, float y, Math::Color* color)
{
	SHADER.m_spriteShader.DrawPoint(x, y, color);
}

void DrawMoji(float x, float y, char* p_str, Math::Color* color, bool Shadow, float SAlpha)
{
	if (Shadow)
	{
		SHADER.m_spriteShader.DrawString(x + 3, y - 3, p_str, Math::Vector4(0.1, 0.1, 0.1, 1));
	}
	SHADER.m_spriteShader.DrawString(x, y, p_str, *color);
}

float DegToRad(float a_deg)
{
	return DirectX::XMConvertToRadians(a_deg);
}

float Rnd()
{
	return rand() / (float)RAND_MAX;
}

bool GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

int BoolToInt(bool a)
{
	if (a)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float GetDist(Math::Vector2 Apos, Math::Vector2 Bpos)
{
	float distX = Apos.x - Bpos.x;
	float distY = Apos.y - Bpos.y;
	float dist = sqrtf(distX * distX + distY * distY);

	return dist;
}

float GetRadian(Math::Vector2 Apos, Math::Vector2 Bpos)
{
	float x = Bpos.x - Apos.x;
	float y = Bpos.y - Apos.y;
	float radian = atan2(y, x);

	return radian;
}

Math::Matrix CreateScale(float a, float b, float c)
{
	return Math::Matrix::CreateScale(a, b, c);
}