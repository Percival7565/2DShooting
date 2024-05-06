#include "EnemyA.h"
#include "../../Scene/Scene.h"

void C_EnemyA::Init()
{
	//m_pos = { 0,0 };
	frame = 0;
	m_bFlg = true;
	angle = 0;

	//敵
	m_tex.Load("Texture/Enemy/demo_enemy.png"); 
	m_B_BulTex.Load("Texture/Bullet/y_bullet.png");
}

void C_EnemyA::Update()
{
	frame++;

	angle += 1.0f;
	if (angle >= 350.0f)
	{
		angle -= 360.0f;
	}
	m_pos.y = sin(DirectX::XMConvertToRadians(angle)) * 300;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		//m_pos.y++;
	}

	if (m_bFlg)
	{

		//弾の発射処理
		if (frame % 20 == 0)
		{
			//if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				// m_bulletList[b].GetAlive==falseの時

				//C_Bullet* tempBullet = new C_Bullet();
				std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

				tempBullet->Init();

				tempBullet->SetTexture(&m_B_BulTex);

				tempBullet->Shot(m_pos, 1);

				//m_bulletList.push_back(tempBullet);	// push_back : 配列の末尾にデータを追加する
				m_pOwner->AddBullet(tempBullet);

				//frame = 0;
			}
		}
	}

	//for (int b = 0; b < m_bulletList.size(); b++)
	//{
	//	m_bulletList[b]->Update();
	//}

	//// 可変長配列をポインタ操作するイテレーター（リモコン）
	//// イテレーターは毛偏重配列のアドレスを格納できる

	//std::vector <C_Bullet*>::iterator it;	// 可変長配列

	//it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納

	//while (it != m_bulletList.end())
	//{
	//	const bool bAlive = (*it)->GetAlive();
	//	if (!bAlive)
	//	{
	//		delete (*it);
	//		it = m_bulletList.erase(it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
	//	}
	//	else
	//	{
	//		it++;
	//	}
	//}

	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_smat = Math::Matrix::CreateScale(-1, 1, 0);
	m_mat = m_smat * m_tmat;
}

void C_EnemyA::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	DrawImg(m_mat, &m_tex, { 0,0,64,64 }, 1.0f);

}
