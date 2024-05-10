#include "EnemyD.h"
#include "../../Scene/Scene.h"

void C_EnemyD::Init()
{
	//m_pos = { 0,0 };
	frame = 0;
	frame2 = 0;
	frame3 = 0;
	m_bFlg = true;
	angle = 0;

	//敵
	m_tex.Load("Texture/Enemy/enemy.png");
	m_BulTex.Load("Texture/Bullet/bullet.png");
	m_spawnTex.Load("Texture/Enemy/enemy_spawn.png");
	m_C_kasanTex.Load("Texture/Kasan/kasan_color.png");

	m_enemyAnimeCnt = 0;

	m_spawnAnimeCnt = 0;
}

void C_EnemyD::Update()
{
	angle += 1.0f;
	if (angle >= 350.0f)
	{
		angle -= 360.0f;
	}

	switch (m_enemyMoveType)
	{
	case 0:
		break;
	case 1:

		m_pos.x -= 10;

		if (m_pos.x < -700)
		{
			m_pos.x = 700;
		}
		break;
	case 2:
		m_pos.y = sin(DirectX::XMConvertToRadians(angle)) * 300 * 0.5f;
		break;
	case 3:
		m_pos.x -= 10;

		if (m_pos.x < -700)
		{
			m_pos.x = 700;
		}
		m_pos.y = sin(DirectX::XMConvertToRadians(angle)) * 300 * 0.5f;
		break;
	}



	//このコメントを外すと敵がサインカーブする
	//m_pos.y = sin(DirectX::XMConvertToRadians(angle)) * 300 * 0.5f;

	//とりあえず
	//m_pos.y -= 5;

	if (frame >= 300)
	{
		m_beemFlg = true;
	}
	else
	{
		frame++;
		m_beemFlg = false;
	}

	if (m_bFlg)
	{

		//弾の発射処理
		if (frame >= 20)
		{

			std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

			tempBullet->Init();

			tempBullet->SetTexture(&m_BulTex);

			tempBullet->SetEnemyColor(EnemyGreen);

			tempBullet->Shot({ m_pos.x - 10, m_pos.y }, 7);

			//m_bulletList.push_back(tempBullet);	// push_back : 配列の末尾にデータを追加する
			m_pOwner->AddBullet(tempBullet);

			frame = 0;

		}
	}

	frame2++;

	if (frame2 > 10)
	{
		m_enemyAnimeCnt++;
		frame2 = 0;
		if (m_enemyAnimeCnt >= 5)
		{
			m_enemyAnimeCnt = 0;
		}
	}

	frame3++;

	if (m_spawnAnimeCnt <= 4)
	{
		if (frame3 > 2)
		{
			m_spawnAnimeCnt++;
			frame3 = 0;
		}
	}

	//m_spawnAnimeCnt++;

	m_tmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_smat = Math::Matrix::CreateScale(-1, 1, 0);
	m_mat = m_smat * m_tmat;

	m_tspawnMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_sspawnMat = Math::Matrix::CreateScale(2, 2, 0);
	m_spawnMat = m_sspawnMat * m_tspawnMat;
}

void C_EnemyD::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	D3D.SetBlendState(BlendMode::Add);
	DrawImg(m_spawnMat, &m_C_kasanTex, { 192,0,64,64 }, 1.0f);	//色付きの加算合成
	D3D.SetBlendState(BlendMode::Alpha);

	switch (m_enemyAnimeCnt)
	{
	case 0:
		DrawImg(m_mat, &m_tex, { 0,192,64,64 }, 1.0f);
		break;
	case 1:
		DrawImg(m_mat, &m_tex, { 64,192,64,64 }, 1.0f);
		break;
	case 2:
		DrawImg(m_mat, &m_tex, { 128,192,64,64 }, 1.0f);
		break;
	case 3:
		DrawImg(m_mat, &m_tex, { 192,192,64,64 }, 1.0f);
		break;
	case 4:
		DrawImg(m_mat, &m_tex, { 256,192,64,64 }, 1.0f);
		break;
	}

	D3D.SetBlendState(BlendMode::Add);

	switch (m_spawnAnimeCnt)
	{
	case 0:
		DrawImg(m_spawnMat, &m_spawnTex, { 0,192,64,64 }, 1.0f);
		break;
	case 1:
		DrawImg(m_spawnMat, &m_spawnTex, { 64,192,64,64 }, 1.0f);
		break;
	case 2:
		DrawImg(m_spawnMat, &m_spawnTex, { 128,192,64,64 }, 1.0f);
		break;
	case 3:
		DrawImg(m_spawnMat, &m_spawnTex, { 192,192,64,64 }, 1.0f);
		break;
	case 4:
		DrawImg(m_spawnMat, &m_spawnTex, { 256,192,64,64 }, 1.0f);
		break;
	}
	D3D.SetBlendState(BlendMode::Alpha);
}
