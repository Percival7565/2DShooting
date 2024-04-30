#include "../Scene/Scene.h"
#include "Player.h"

void C_Player::Init()
{
	m_pos = { 0,0 };
	frame = 0;
	m_bFlg = true;
}

void C_Player::Update()
{
	frame++;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x = m_pos.x + 10;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x = m_pos.x - 10;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y = m_pos.y + 10;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y = m_pos.y - 10;
	}

	//弾の発射処理
	if (frame >= 10)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
		{
			// m_bulletList[b].GetAlive==falseの時

			C_Bullet* tempBullet = new C_Bullet();

			tempBullet->Init();

			tempBullet->SetTexture(m_pBulletTex);

			tempBullet->Shot(m_pos,0);

			m_bulletList.push_back(tempBullet);	// push_back : 配列の末尾にデータを追加する

			frame = 0;
		}
	}

	//								 size() : 現在の配列要素数
	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update();
	}

	// 可変長配列をポインタ操作するイテレーター（リモコン）
	// イテレーターは毛偏重配列のアドレスを格納できる

	std::vector <C_Bullet*>::iterator it;	// 可変長配列

	it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納

	while (it != m_bulletList.end())
	{
		const bool bAlive = (*it)->GetAlive();
		if (!bAlive)
		{
			delete (*it);
			it = m_bulletList.erase(it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			it++;
		}
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Player::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	DrawImg(m_mat, m_pTex, { 0,0,64,64 }, 1.0f);

	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw(0);
	}

}

HitStruct C_Player::GetObj()
{
	HitStruct m_Obj;
	m_Obj.pos = m_pos;
	m_Obj.rad = {50,50};
	m_Obj.move = {0,0};
	m_Obj.bActive = m_bFlg;

	return HitStruct(m_Obj);
}
