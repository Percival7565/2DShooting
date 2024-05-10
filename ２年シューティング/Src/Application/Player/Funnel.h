#pragma once

class Scene;

class C_Funnel
{
public:
	C_Funnel(){}
	~C_Funnel(){}

	void Init();
	void Update(Math::Vector2 a_pos);
	void Draw();

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetPause(bool a_flg) { m_funnelPause = a_flg; }
	void SetBulSpeed(int a_speed) { m_funnelBulSpeed = a_speed; }

private:

	int frame;
	int bulframe;
	int animeframe;

	bool m_funnelPause;

	KdTexture m_Tex;	//画像
	KdTexture m_bulletTex;	//画像
	Math::Vector2 m_pos;//座標
	Math::Matrix m_mat;	//行列
	Math::Matrix m_smat;	//行列
	Math::Matrix m_rmat;	//行列
	Math::Matrix m_tmat;	//行列

	Math::Vector2 m_target;
	float m_smallest;
	float m_smallestNext;
	Math::Vector2 m_smallestPos;

	int m_funnelAnimeCnt;
	int m_funnelBulSpeed;
	float m_funnelBulFast;

	float m_angle;

	Scene* m_pOwner;

};