#pragma once

class C_Bullet
{
public:
	void Init();	//������
	void Update();	//�X�V
	void Draw(int bulletType);	//�`��

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//���ˏ���

	void Hit();		//��������

	//�Q�b�^�[(�ق��̃N���X�֒l�������Ă���)
	const bool GetAlive();
	const Math::Vector2 GetPos();
	const float GetRadius();

	//�Z�b�^�[
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:
	KdTexture* m_pTex;		//�摜
	Math::Vector2 m_pos;	//���W
	Math::Matrix m_mat;		//�s��
	bool m_bAlive;			//�t���O

	Math::Vector2 m_move;	//�ړ���

	const float TEX_RADIUS = 8.0f;	//���a

	int bulletType;

};