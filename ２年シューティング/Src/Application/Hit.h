#pragma once

class Scene;

class C_Hit
{
public:

	void Init();
	void Update();
	void Draw();

	// セッター
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	bool GetHitbullet(HitStruct b0,HitStruct b1);

	bool GetHitJet(HitStruct player,HitStruct enemy);

private:


	Scene* m_pOwner;

};

