#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

//--------------------------------
// コンストラクタ
//--------------------------------
Help::Help() {
	//image = LoadGraph("images/help.png");
	//ヘルプ画面読み込み
	if ((HelpImage = LoadGraph("Resource/Images/Help.png")) == -1)
	{
		throw "Resource/Images/Help.png";
	}
	//BGMの読み込み
	if ((HelpBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, HelpBGM);

	//SEの読み込み
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(125, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
Help::~Help()
{
	//サウンドの削除
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(DecisionSE);
}

//--------------------------------
// 更新
//--------------------------------
AbstractScene* Help::Update() 
{
	

	//Bボタンでタイトルへ戻る
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new Title();
	}
	//Aボタンでゲームを始める
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) 
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new GameMain();
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void Help::Draw()const 
{
	DrawGraph(0, 0, HelpImage, FALSE);
}