#include "../Scene/Scene.h"
#include"Sound.h"

void C_Sound::Init()
{
	// Œø‰Ê‰¹‚Ì“Ç‚İ‚İ‚Æ‰Šú‰»
	for (int i = 0; i < se_End; i++)
	{
		switch (i)
		{
		case se_Shot:
			InitSE("Sound/Se/shot.wav", 0.10f, i);
			break;
		case se_Lost:
			InitSE("Sound/Se/lost.wav", 0.10f, i);
			break;
		case se_Push:
			InitSE("Sound/Se/push.wav", 0.20f, i);
			break;
		case se_Roll:
			InitSE("Sound/Se/roll.wav", 0.50f, i);
			break;
		case se_Wave:
			InitSE("Sound/Se/wave.wav", 0.50f, i);
			break;
		}
	}

	for (int j = 0; j < bgm_End; j++)
	{
		switch (j)
		{
		case bgm_Title:
			InitBGM("Sound/Bgm/title.wav", 0.05f, j);
			break;
		case bgm_Game:
			InitBGM("Sound/Bgm/game.wav", 0.10f, j);
			break;
		}
	}
}

void C_Sound::Update()
{

}

void C_Sound::StopAll()
{
	// SE‘S•”~‚ß‚é
	for (int i = 0; i < se_End; i++)
	{
		SE_Inst[i]->Stop();
	}

	for (int j = 0; j < bgm_End; j++)
	{
		BGM_Inst[j]->Stop();
	}
}

void C_Sound::InitSE(string file, float avol, int num)
{
	SE[num] = std::make_shared<KdSoundEffect>();

	SE[num]->Load(file);

	SE_Inst[num] = SE[num]->CreateInstance(false);

	SE_Inst[num]->SetVolume(avol);
}

void C_Sound::InitBGM(string file, float avol, int num)
{
	// BGM‚Ì“Ç‚İ‚İ‚Æ‰Šú‰»
	BGM[num] = std::make_shared<KdSoundEffect>();

	BGM[num]->Load(file);

	BGM_Inst[num] = BGM[num]->CreateInstance(false);

	BGM_Inst[num]->SetVolume(avol);

	//BGM_Inst[num]->Play(true);
}
