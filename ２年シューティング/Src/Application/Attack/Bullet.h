#pragma once

class C_Bullet
{
public:
	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��

	void Shot(Math::Vector2 a_shotPos,int BulletType);	//���ˏ���
	void Shot(Math::Vector2 a_shotPos,int BulletType,Math::Vector2 a_targetPos,float a_bulSpeed);	//���ˏ����̃I�[�o�[���C�h

	const bool GetAlive();
	const Math::Vector2 GetPos();

	int GetBulletType() { return m_bulletType; }
	float GetEnemyBulSize() { return enemyBulSize; }
	float GetPlayerBulSize() { return playerBulSize; }

	//�Z�b�^�[
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetColor(int a_color) { m_PlayerColor = a_color; }
	void SetEnemyColor(int a_Ecolor) { m_EnemyColor = a_Ecolor; }

	void SetAlive(bool a_bAlive) { m_bAlive = a_bAlive; }

	void SetPlayerBulSize(float a_PbulSize) { playerBulSize = a_PbulSize; }//�����g���
	void SetPlayerBulSizeLv(int a_PbulSizeLevel) { playerBulSizeLv = a_PbulSizeLevel; }

private:
	KdTexture* m_pTex;		
	Math::Vector2 m_pos;	
	Math::Vector2 m_size;	
	Math::Matrix m_tmat;		
	Math::Matrix m_smat;		
	Math::Matrix m_mat;		
	Math::Matrix m_enemyMat;
	bool m_bAlive;

	Math::Vector2 m_move;	//�ړ���

	const float TEX_RADIUS = 8.0f;	//���a

	int m_bulletType;
	int m_PlayerColor;
	int m_EnemyColor;

	KdTexture m_kasanTex;

	float enemyBulSize;
	float playerBulSize;
	int playerBulSizeLv;
};