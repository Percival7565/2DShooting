#include "../Scene/Scene.h"
#include "BaseEnemy.h"

void C_BaseEnemy::Init()
{
}

void C_BaseEnemy::Update()
{

}

void C_BaseEnemy::Draw()
{
	
}

HitStruct C_BaseEnemy::GetObj()
{
	HitStruct m_Obj;
	m_Obj.pos = m_pos;
	m_Obj.rad = { 50,50 };
	m_Obj.move = { 0,0 };
	m_Obj.bActive = m_bFlg;

	return HitStruct(m_Obj);
}