#pragma once
#include"../BaseEnemy.h"

class C_EnemyC : public C_BaseEnemy
{
public:

	C_EnemyC() {}
	~C_EnemyC() {}

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	bool m_beemFlg;

};