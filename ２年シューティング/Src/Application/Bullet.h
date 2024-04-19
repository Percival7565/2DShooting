#pragma once

class C_Bullet
{
public:
	void Init();	//初期化
	void Update();	//更新
	void Draw(int bulletType);	//描画

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//発射処理

	void Hit();		//当たった

	//ゲッター(ほかのクラスへ値を持っていく)
	const bool GetAlive();
	const Math::Vector2 GetPos();
	const float GetRadius();

	//セッター
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:
	KdTexture* m_pTex;		//画像
	Math::Vector2 m_pos;	//座標
	Math::Matrix m_mat;		//行列
	bool m_bAlive;			//フラグ

	Math::Vector2 m_move;	//移動量

	const float TEX_RADIUS = 8.0f;	//半径

	int bulletType;

};