#pragma once

class C_Bullet
{
public:
	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//発射処理

	//ゲッター(ほかのクラスへ値を持っていく)
	const bool GetAlive();
	const Math::Vector2 GetPos();
	const float GetRadius();

	int GetBulletType() { return m_bulletType; }

	//セッター
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetAlive(bool a_bAlive) { m_bAlive = a_bAlive; }

private:
	KdTexture* m_pTex;		//画像
	Math::Vector2 m_pos;	//座標
	Math::Matrix m_mat;		//行列
	bool m_bAlive;			//フラグ

	Math::Vector2 m_move;	//移動量

	const float TEX_RADIUS = 8.0f;	//半径

	int m_bulletType;

};