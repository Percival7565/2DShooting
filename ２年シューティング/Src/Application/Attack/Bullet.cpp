#include "Bullet.h"
#include "../Scene/Utility.h"

void C_Bullet::Init()
{
	m_pos = Math::Vector2(0, 0);
	m_move = Math::Vector2(0, 0);
	m_bAlive = false;
	m_mat = Math::Matrix::Identity;
	m_pTex = nullptr;

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

	m_pos +=  m_move;


	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Bullet::Draw(int bulletType)
{
	if (!m_bAlive) return;	//早期リターン

	switch (bulletType)
	{
	case 0:
		DrawImg(m_mat, m_pTex, { 0,0,7,7 }, 1.0f);
		break;
	case 1:
		DrawImg(m_mat, m_pTex, { 0,0,16,16 }, 1.0f);
		break;
	}
	//DrawImg(m_mat, m_pTex, { 0,0,7,7 }, 1.0f);
}

void C_Bullet::Shot(Math::Vector2 a_shotPos,int bulletType)
{
	m_pos = a_shotPos;		//発射される座標
	m_bAlive = true;		//発射状態


	switch (bulletType)
	{
	case 0:
		m_move.x = 25.0f;
		break;
	case 1:
		m_move.x = -10.0f;
		break;
	}
	
}

void C_Bullet::Hit()
{
	m_bAlive = false;

}

const bool C_Bullet::GetAlive()
{
	return m_bAlive;
}

const Math::Vector2 C_Bullet::GetPos()
{
	return m_pos;
}

const float C_Bullet::GetRadius()
{

	return TEX_RADIUS;
}
