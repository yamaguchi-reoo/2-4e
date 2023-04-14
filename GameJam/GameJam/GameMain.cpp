#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"

#define TIMER 180

GameMain::GameMain()
{
	//������
	Level = 0;
	TotalScore = 0;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		Score[i] = 0;
	}
	ClimbingTimer = TIMER;
	MissTimer = TIMER;
	//�I�u�W�F�N�g��
	trampoline = new Trampoline();
	player = new Player();
	wall = new Wall();
	stage = new Stage();

	//BGM�̓ǂݍ���
	if ((GameBGM = LoadSoundMem("Resource/sounds/BGM/Jackpot.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Jackpot.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, GameBGM);

	//�t�H���g�̐ݒ�
	ScoreFont[0] = CreateFontToHandle("Score1", 20, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	ScoreFont[1] = CreateFontToHandle("Score2", 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	//BGM�̍Đ�
	if (CheckSoundMem(GameBGM) == 0) {
		PlaySoundMem(GameBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

GameMain::~GameMain()
{
	//�I�u�W�F�N�g�̍폜
	delete trampoline;
	delete player;
	delete wall;
	delete stage;

	//�t�H���g�̍폜
	for (int i = 0; i < 2; i++)
	{
		DeleteFontToHandle(ScoreFont[i]);
	}

	//BGM�̍폜
	DeleteSoundMem(GameBGM);
}

AbstractScene* GameMain::Update()
{
	//�����̍X�V
	player->UpDate();
	trampoline->UpDate();
	if (ClimbingTimer == TIMER)
	{
		wall->UpDate();
	}

	

	//�v���C���[�ƃg�����|�����̓����蔻��
	if (trampoline->HitBox(player))	//�v���C���[�Ɠ���������
	{
		if (trampoline->GetState() == TRAMPOLINE_STATE::IDOL) //�A�C�h����ԂȂ�
		{
			trampoline->GetPoint();
		}
		player->HitTrampoline();
	}
	else if (trampoline->GetState() == TRAMPOLINE_STATE::PRESS) //���܂�Ă���Ȃ�
	{
		trampoline->Extend();
		player->LeaveTrampoline();
	}
	else {}

	//�ǂƓ�����Ȃ�����
	if ((trampoline->GetLocation().x + trampoline->GetErea().width / 2 < player->GetLocation().x) && (player->GetLocation().y >= 500))
	{
		if (MissTimer == TIMER)
		{
			player->MissJump();
		}
		if (--MissTimer < 0)
		{
			Score[Level] = 0;
			TotalScore += Score[Level];
			Level++;
			player->Reset();
			wall->NextStage(Level);
			MissTimer = TIMER;
		}
	}

	//�v���C���[�ƕǂƂ̓����蔻��
	else if (wall->HitBox(player))
	{
		if (ClimbingTimer == TIMER)
		{
			player->HitWall();
		}
		if (--ClimbingTimer < 0)
		{
			Score[Level] = wall->GetPoint(player->GetLocation().y - 30);
			TotalScore += Score[Level];
			Level++;
			player->Reset();
			wall->NextStage(Level);
			ClimbingTimer = TIMER;
		}
	}

	//�Q�[���I��
	if (MAX_LEVEL <= Level)
	{
		StopSoundMem(GameBGM);
		return new Result(TotalScore, Score);
	}

	return this;
}

void GameMain::Draw()const
{
	//�X�e�[�W�̕`��
	stage->Draw();
	//�g�����|�����̕`��
	trampoline->Draw();
	//�ǂ̕`��
	wall->Draw();

	//�v���C���[�̕`��
	player->Draw();

	//�X�R�A�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(20, 20,320, 220, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		DrawFormatStringToHandle(30, 60 + (30 * i), 0xffffff, ScoreFont[0], "%d�X�e�[�W�F%3dpt", i + 1, Score[i]);
	}
	DrawFormatStringToHandle(30, 30, 0xffffff, ScoreFont[1], "TotalScore :%4dpt", TotalScore);
}

