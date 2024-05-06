#pragma once

class C_Bullet
{
public:
	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//���ˏ���

	//�Q�b�^�[(�ق��̃N���X�֒l�������Ă���)
	const bool GetAlive();
	const Math::Vector2 GetPos();
	const float GetRadius();

	int GetBulletType() { return m_bulletType; }

	//�Z�b�^�[
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetAlive(bool a_bAlive) { m_bAlive = a_bAlive; }

private:
	KdTexture* m_pTex;		//�摜
	Math::Vector2 m_pos;	//���W
	Math::Matrix m_mat;		//�s��
	bool m_bAlive;			//�t���O

	Math::Vector2 m_move;	//�ړ���

	const float TEX_RADIUS = 8.0f;	//���a

	int m_bulletType;

};