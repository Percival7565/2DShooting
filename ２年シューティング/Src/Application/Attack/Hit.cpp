#include "../Scene/Scene.h"

#include "Hit.h"

void C_Hit::Init()
{

}

void C_Hit::Update()
{
}

void C_Hit::Draw()
{
}

void C_Hit::GetHitbullet()
{
	
	
}

void C_Hit::GetHitJet()
{
	for (auto& enemy : m_pOwner ->GetEnemyAList())
	{
		if (enemy->GetFlg())
		{
			if (m_player->GetFlg())
			{
				// ���W�Ώ� - �������W�@= �Ώۂւ̃x�N�g��
				Math::Vector2 v;
				v = enemy->GetPos() - m_player->GetPos();

				// ������
				if (v.Length() < 64.0f)
				{
					//obj->OnHit();

					//m_player->SetFlg(false);
					m_player->SetHp(m_player->GetHp() - 1);
					enemy->SetFlg(false);
					//m_WaveEnemyNum--;
					m_pOwner->SetEnemyNum(m_pOwner->GetEnemyNum() - 1);
				}
			}
		}
	}

	for (auto& enemy : m_pOwner->GetEnemyBList())
	{
		if (enemy->GetFlg())
		{
			if (m_player->GetFlg())
			{
				// ���W�Ώ� - �������W�@= �Ώۂւ̃x�N�g��
				Math::Vector2 v;
				v = enemy->GetPos() - m_player->GetPos();

				// ������
				if (v.Length() < 64.0f)
				{
					//obj->OnHit();

					//m_player->SetFlg(false);
					m_player->SetHp(m_player->GetHp() - 1);
					enemy->SetFlg(false);
					//m_WaveEnemyNum--;
					m_pOwner->SetEnemyNum(m_pOwner->GetEnemyNum() - 1);
				}
			}
		}
	}

	for (auto& enemy : m_pOwner->GetEnemyCList())
	{
		if (enemy->GetFlg())
		{
			if (m_player->GetFlg())
			{
				// ���W�Ώ� - �������W�@= �Ώۂւ̃x�N�g��
				Math::Vector2 v;
				v = enemy->GetPos() - m_player->GetPos();

				// ������
				if (v.Length() < 64.0f)
				{
					//obj->OnHit();

					//m_player->SetFlg(false);
					m_player->SetHp(m_player->GetHp() - 1);
					enemy->SetFlg(false);
					//m_WaveEnemyNum--;
					m_pOwner->SetEnemyNum(m_pOwner->GetEnemyNum() - 1);
				}
			}
		}
	}

	for (auto& enemy : m_pOwner->GetEnemyDList())
	{
		if (enemy->GetFlg())
		{
			if (m_player->GetFlg())
			{
				// ���W�Ώ� - �������W�@= �Ώۂւ̃x�N�g��
				Math::Vector2 v;
				v = enemy->GetPos() - m_player->GetPos();

				// ������
				if (v.Length() < 64.0f)
				{
					//obj->OnHit();

					//m_player->SetFlg(false);
					m_player->SetHp(m_player->GetHp() - 1);
					enemy->SetFlg(false);
					//m_WaveEnemyNum--;
					m_pOwner->SetEnemyNum(m_pOwner->GetEnemyNum() - 1);
				}
			}
		}
	}
}
