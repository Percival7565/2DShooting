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
	void SetPlayer(C_Player* a_player) { m_player = a_player; }

	void GetHitbullet();

	void GetHitJet();

private:

	C_Player* m_player;
	Scene* m_pOwner;

};

