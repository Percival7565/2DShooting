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
	for (auto& obj : m_pOwner ->GetEnemyAList())
	{
		
		// ���W�Ώ� - �������W�@= �Ώۂւ̃x�N�g��
		Math::Vector2 v;
		v = obj->GetPos() - m_player->GetPos();

		// ������
		if (v.Length() < 64.0f)
		{
			//obj->OnHit();

			m_player->SetFlg(false);
			obj->SetFlg(false);
		}
		
	}
}
