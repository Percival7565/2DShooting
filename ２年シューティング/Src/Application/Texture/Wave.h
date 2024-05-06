#pragma once

#include "Number.h"

class C_Wave
{
public:
	C_Wave() {}
	~C_Wave(){}

	void Init();
	void Update();
	void Draw();

private:

	C_Number m_number;
	float NumAlpha;
	Math::Vector2 m_numPos;
	float m_addPos;

	KdTexture m_waveTex;
	Math::Vector2 m_pos;
	Math::Vector2 m_sc;
	Math::Matrix m_mat;
	Math::Matrix m_tmat;
	Math::Matrix m_smat;

	float m_waveAlpha;

};