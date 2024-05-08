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

	void SetWaveNum(int a_num) { m_WaveNum = a_num; }

	void SetWaveFlg(bool a_flg) { m_WaveFlg = a_flg; }

	void SetWaveScale(Math::Vector2 a_sc) { m_sc = a_sc; }

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

	int m_WaveNum;

	bool m_WaveFlg;

	KdTexture m_blindTex;
	Math::Matrix m_Bmat;

};