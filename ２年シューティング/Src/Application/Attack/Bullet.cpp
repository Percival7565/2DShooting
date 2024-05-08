#include "Bullet.h"
#include "../Scene/Utility.h"

void C_Bullet::Init()
{
	m_kasanTex.Load("Texture/Bullet/kasan.png");
	m_pos = {};
	m_size = { 1.0f,1.0f };
	m_bAlive = false;
	m_mat = Math::Matrix::Identity;
	m_pTex = nullptr;
	m_bulletType = 0;

	enemyBulSize = 16.0f;
	playerBulSize = 32.0f;
	playerBulSizeLv = 0;

	//m_move.x = 25.0f;
}

void C_Bullet::Update()
{
	if (!m_bAlive) return;	//早期リターン

	//画面外判定
	/*if (m_pos.x > HfWidth || m_pos.x < -HfWidth) m_bAlive = false;
	if (m_pos.y > HfHeight || m_pos.y < -HfHeight) m_bAlive = false;*/
	
	if (m_pos.x > 1280 / 2 || m_pos.x < -1280 / 2)
	{
		m_bAlive = false;
	}
	if (m_pos.y > 720 / 2 || m_pos.y < -720 / 2)
	{
		m_bAlive = false;
	}

	switch (playerBulSizeLv)
	{
	case 0:
		playerBulSize = 32.0f;
		m_size = {1.0f,1.0f};
		break;
	case 1:
		playerBulSize = 37.0f;
		m_size = { 1.5,1.5f };
		break;
	case 2:
		playerBulSize = 42.0f;
		m_size = { 2.0f,2.0f };
		break;
	case 3:
		playerBulSize = 47.0f;
		m_size = { 2.5f,2.5f };
		break;
	case 4:
		playerBulSize = 52.0f;
		m_size = { 3.0f,3.0f };
		break;
	case 5:
		playerBulSize = 57.0f;
		m_size = { 3.5f,3.5f };
		break;
	default:
		break;
	}

	m_pos +=  m_move;

	m_enemyMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_smat = Math::Matrix::CreateScale(m_size.x,m_size.y,0);
	m_mat = m_smat * m_tmat;
}

void C_Bullet::Draw()
{
	if (!m_bAlive) return;	//早期リターン

	D3D.SetBlendState(BlendMode::Add);

	switch (m_bulletType)
	{
	case 0:
		DrawImg(m_mat, &m_kasanTex, { 0,0,16,16 }, 1.0f);
		DrawImg(m_mat, m_pTex, { 0,0,32,32 }, 0.5f);
		break;
	case 1:
		DrawImg(m_enemyMat, &m_kasanTex, { 0,0,16,16 }, 1.0f);
		DrawImg(m_enemyMat, m_pTex, { 0,0,32,32 }, 0.5f);
		break;
	default:
		break;
	}

	D3D.SetBlendState(BlendMode::Alpha);
}

void C_Bullet::Shot(Math::Vector2 a_shotPos,int BulletType)
{
	m_pos = a_shotPos;		//発射される座標
	m_bAlive = true;		//発射状態

	m_bulletType = BulletType;

	switch (BulletType)
	{
	case 0:
		m_move.x = 25.0f;
		break;
	case 1:
		m_move.x = -10.0f;
		break;
	default:
		break;
	}
}

const bool C_Bullet::GetAlive()
{
	return m_bAlive;
}

const Math::Vector2 C_Bullet::GetPos()
{
	return m_pos;
}

