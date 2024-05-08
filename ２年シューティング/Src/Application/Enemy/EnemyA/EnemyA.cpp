#include "EnemyA.h"
#include "../../Scene/Scene.h"

void C_EnemyA::Init()
{
	//m_pos = { 0,0 };
	frame = 0;
	frame2 = 0;
	frame3 = 0;
	m_bFlg = true;
	angle = 0;

	//敵
	m_tex.Load("Texture/Enemy/enemy.png");
	m_B_BulTex.Load("Texture/Bullet/enemy_bullet.png");
	m_spawnTex.Load("Texture/Enemy/enemy_spawn.png");
	m_C_kasanTex.Load("Texture/Kasan/kasan_color.png");

	m_enemyAnimeCnt = 0;

	m_spawnAnimeCnt = 0;
}

void C_EnemyA::Update()
{
	frame++;

	angle += 1.0f;
	if (angle >= 350.0f)
	{
		angle -= 360.0f;
	}

	//このコメントを外すと敵がサインカーブする
	//m_pos.y = sin(DirectX::XMConvertToRadians(angle)) * 300 * 0.5f;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		//m_pos.y++;
		m_pos.x--;
	}

	//とりあえず
	m_pos.x--;

	if (m_bFlg)
	{

		//弾の発射処理
		if (frame >= 110)
		{

			std::shared_ptr<C_Bullet> tempBullet = std::make_shared<C_Bullet>();

			tempBullet->Init();

			tempBullet->SetTexture(&m_B_BulTex);

			tempBullet->Shot(m_pos, 1);

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

void C_EnemyA::Draw()
{
	if (!m_bFlg)
	{
		return;
	}

	D3D.SetBlendState(BlendMode::Add);
	DrawImg(m_spawnMat, &m_C_kasanTex, { 0,0,64,64 }, 1.0f);	//色付きの加算合成
	D3D.SetBlendState(BlendMode::Alpha);

	switch (m_enemyAnimeCnt)
	{
	case 0:
		DrawImg(m_mat, &m_tex, { 0,0,64,64 }, 1.0f);
		break;
	case 1:
		DrawImg(m_mat, &m_tex, { 64,0,64,64 }, 1.0f);
		break;
	case 2:
		DrawImg(m_mat, &m_tex, { 128,0,64,64 }, 1.0f);
		break;
	case 3:
		DrawImg(m_mat, &m_tex, { 192,0,64,64 }, 1.0f);
		break;
	case 4:
		DrawImg(m_mat, &m_tex, { 256,0,64,64 }, 1.0f);
		break;
	}

	D3D.SetBlendState(BlendMode::Add);

	switch (m_spawnAnimeCnt)
	{
	case 0:
		DrawImg(m_spawnMat, &m_spawnTex, { 0,0,64,64 }, 1.0f);
		break;
	case 1:
		DrawImg(m_spawnMat, &m_spawnTex, { 64,0,64,64 }, 1.0f);
		break;
	case 2:
		DrawImg(m_spawnMat, &m_spawnTex, { 128,0,64,64 }, 1.0f);
		break;
	case 3:
		DrawImg(m_spawnMat, &m_spawnTex, { 192,0,64,64 }, 1.0f);
		break;
	case 4:
		DrawImg(m_spawnMat, &m_spawnTex, { 256,0,64,64 }, 1.0f);
		break;
	}
	D3D.SetBlendState(BlendMode::Alpha);
}
