#pragma once

class C_Player;

class C_Ability
{
public:
	C_Ability() {}
	~C_Ability() {}

	void Init();
	void Update();
	void Draw();
	void SelectAbility();
	void SetGetAbi(int a_GetAbi) { m_GetAbi = a_GetAbi; }

	int GetSelectAbi() { return m_GetAbi; }

	void Stop();

private:

	C_Player m_player;

	KdTexture m_abiATex;
	KdTexture m_abiBTex;
	KdTexture m_abiCTex;
	KdTexture m_abiDTex;
	KdTexture m_abiETex;

	Math::Vector2 m_pos;
	Math::Vector2 m_sc;
	Math::Matrix m_mat;
	Math::Matrix m_tmat;
	Math::Matrix m_smat;

	float m_abiAalpha;
	float m_rollspead;
	bool m_rollstopFlg;

	int m_SelectAbi;
	int m_GetAbi;
};