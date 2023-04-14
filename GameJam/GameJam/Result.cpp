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


	//�w�i�摜�̓ǂݍ���
	if ((Image = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}

	//�t�H���g�̐ݒ�
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	NomalFont = CreateFontToHandle("Nomal", 48, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	GuideFont = CreateFontToHandle("Guide", 32, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//BGM�ǂݍ���
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.mp3";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, RankingBGM);

	//����{�^����SE
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.mp3";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(200, DecisionSE);

	//BGM�̍Đ�
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

Result::~Result()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(HeadLineFont);
	DeleteFontToHandle(NomalFont);
	DeleteFontToHandle(GuideFont);

	//�T�E���h�̍폜
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

	//���v�X�R�A�`��
	DrawStringToHandle(200, 250, "���v�X�R�A", 0x000000,HeadLineFont);
	DrawFormatStringToHandle(250, 350, 0x000000, HeadLineFont, "%4dpt",TotalScore);

	//�e�X�e�[�W�̃X�R�A�̕`��
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		DrawFormatStringToHandle(650, 230 + (50 * i), 0x000000, NomalFont,"%d�X�e�[�W�F%3dpt",i + 1, Score[i]);
	}

	DrawFormatStringToHandle(400, 550, 0x00ff00,GuideFont, "%d�b��Ƀ����L���O��ʂɈړ�", WaitTime / 60);
	DrawStringToHandle(500, 600, "A�{�^���ŃX�L�b�v",0x00ff00,GuideFont);
}