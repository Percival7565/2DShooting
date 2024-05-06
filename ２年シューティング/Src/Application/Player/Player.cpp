#include "../Scene/Scene.h"
#include "Player.h"

void C_Player::Init()
{
	m_playerTex.Load("Texture/Player/demo_jet.png");
	m_BulletTex.Load("Texture/Bullet/demo_bullet.png");
	m_pos = { -500,0 };
	//m_pos = { 0,0 };
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

	if (m_bFlg)
	{

		//�e�̔��ˏ���
		if (frame >= 2 )
		{
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				// m_bulletList[b].GetAlive==false�̎�

				//C_Bullet* tempBullet = new C_Bullet();
				std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

				tempBullet->Init();

				tempBullet->SetTexture(&m_BulletTex);

				tempBullet->Shot(m_pos, 0);

				//m_bulletList.push_back(tempBullet);	// push_back : �z��̖����Ƀf�[�^��ǉ�����
				m_pOwner->AddBullet(tempBullet);

				frame = 0;
			}
		}
	}

	//for (int b = 0; b < m_bulletList.size(); b++)
	//{
	//	m_bulletList[b]->Update();
	//}

	//// �ϒ��z����|�C���^���삷��C�e���[�^�[�i�����R���j
	//// �C�e���[�^�[�͖ѕΏd�z��̃A�h���X���i�[�ł���

	//std::vector<std::shared_ptr<C_Bullet>>::iterator it;	// �ϒ��z��

	//it = m_bulletList.begin();	// �ϒ��z��̐擪�A�h���X���i�[

	//while (it != m_bulletList.end())
	//{
	//	const bool bAlive = (*it)->GetAlive();
	//	if (!bAlive)
	//	{
	//		//delete (*it);
	//		it = m_bulletList.erase(it);	// �����폜���č폜���锠�̎��̃A�h���X���C�e���[�^�[�Ɋi�[
	//	}
	//	else
	//	{
	//		it++;
	//	}
	//}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Player::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	DrawImg(m_mat, &m_playerTex, { 0,0,64,64 }, 1.0f);

	/*for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw(0);
	}*/

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
