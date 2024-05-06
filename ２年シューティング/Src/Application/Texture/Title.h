#pragma once

class C_Title
{
public:
	C_Title() {}
	~C_Title() {}

	void Init();
	void Update();
	void Draw();
private:

	int frame;

	//�m�[�}��
	KdTexture m_neonATex;
	Math::Vector2 m_neonAPos;
	Math::Matrix m_neonAMat;

	float m_Aalpha;

	//���邢
	KdTexture m_neonBTex;
	Math::Vector2 m_neonBPos;
	Math::Matrix m_neonBMat;

	float m_Balpha;

	//O����
	/*KdTexture m_neonCTex;
	Math::Vector2 m_neonCPos;
	Math::Matrix m_neonCMat;*/

	//����������
	int m_neonTake;
	int m_angle;
};