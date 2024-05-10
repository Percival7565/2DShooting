#pragma once
#include"../BaseEnemy.h"

class C_EnemyD : public C_BaseEnemy
{
public:

	C_EnemyD() {}
	~C_EnemyD() {}

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	bool m_beemFlg;

};