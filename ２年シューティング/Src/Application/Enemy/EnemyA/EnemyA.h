#pragma once
#include"../BaseEnemy.h"

class C_EnemyA : public C_BaseEnemy
{
public:

	C_EnemyA(){}
	~C_EnemyA(){}

	void Init() override;
	void Update() override;
	void Draw() override;

private:

};