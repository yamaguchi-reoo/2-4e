#include "DxLib.h"
#include "Result.h"
#include "Ranking.h"
#include "PadInput.h"
#include "DrawRanking.h"
#include "Define.h"


Result::Result(int total_score, int* score)
{
	TotalScore = total_score;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		Score[i] = score[i];
	}
	WaitTime = WAIT_TIME;
	RANKING::Insert(TotalScore);


	//背景画像の読み込み
	if ((Image = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}

	//フォントの設定
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	NomalFont = CreateFontToHandle("Nomal", 48, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	GuideFont = CreateFontToHandle("Guide", 32, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//BGM読み込み
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.mp3";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, RankingBGM);

	//決定ボタンのSE
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.mp3";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(200, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

Result::~Result()
{
	//フォントの削除
	DeleteFontToHandle(HeadLineFont);
	DeleteFontToHandle(NomalFont);
	DeleteFontToHandle(GuideFont);

	//サウンドの削除
	DeleteSoundMem(DecisionSE);
	DeleteSoundMem(RankingBGM);
}

AbstractScene* Result::Update()
{

	

	if ((PAD_INPUT::OnButton(XINPUT_BUTTON_A)) || (WaitTime-- < 0))
	{
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(RankingBGM);
		return new DrawRanking();
	}

	return this;
}

void Result::Draw() const
{
	DrawGraph(0, 0, Image, TRUE);

	//合計スコア描画
	DrawStringToHandle(200, 250, "合計スコア", 0x000000,HeadLineFont);
	DrawFormatStringToHandle(250, 350, 0x000000, HeadLineFont, "%4dpt",TotalScore);

	//各ステージのスコアの描画
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		DrawFormatStringToHandle(650, 230 + (50 * i), 0x000000, NomalFont,"%dステージ：%3dpt",i + 1, Score[i]);
	}

	DrawFormatStringToHandle(400, 550, 0x00ff00,GuideFont, "%d秒後にランキング画面に移動", WaitTime / 60);
	DrawStringToHandle(500, 600, "Aボタンでスキップ",0x00ff00,GuideFont);
}