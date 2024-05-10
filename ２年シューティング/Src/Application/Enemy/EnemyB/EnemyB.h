#pragma once
#include"../BaseEnemy.h"

class C_EnemyB : public C_BaseEnemy
{
public:

	C_EnemyB() {}
	~C_EnemyB() {}

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	bool m_beemFlg;

};