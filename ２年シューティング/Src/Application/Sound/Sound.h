#pragma once

class Scene;

class C_Sound
{
public:
	C_Sound(){}
	~C_Sound(){}

	void Init();
	void Update();
	void StopAll();

	void InitSE(string file, float avol, int num);
	void InitBGM(string file, float avol, int num);

	//SE	
	std::shared_ptr<KdSoundEffect>		SE[se_End];			// 効果音
	std::shared_ptr<KdSoundInstance>	SE_Inst[se_End];	// 効果音インスタンス
	float								SE_Vol[se_End];		// 音量

	//BGM用
	std::shared_ptr<KdSoundEffect>		BGM[bgm_End];
	std::shared_ptr<KdSoundInstance>	BGM_Inst[bgm_End];
	float								BGM_Vol[bgm_End];		// 音量

private:

};
